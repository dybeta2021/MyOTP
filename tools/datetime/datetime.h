// MIT License
//
// Copyright (c) 2021 kevin lau
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef DATETIME_H_
#define DATETIME_H_

#include <string>

namespace datetime {

constexpr int MINYEAR = 1;
constexpr int MAXYEAR = 9999;
constexpr int MAXORDINAL = 3652059; /* date(9999,12,31).toordinal() */

/* Nine decimal digits is easy to communicate, and leaves enough room
 * so that two delta days can be added w/o fear of overflowing a signed
 * 32-bit int, and with plenty of room left over to absorb any possible
 * carries from adding seconds.
 */
constexpr int MAX_DELTA_DAYS = 999999999;

namespace detail {
struct NotCheckArgsTag {};
struct NotNormalizeTag {};
}  // namespace detail

class timedelta {
 public:
  timedelta() {}
  timedelta(int days, int seconds = 0, int microseconds = 0);
  timedelta(int days, int seconds, int microseconds, int milliseconds,
            int minutes = 0, int hours = 0, int weeks = 0);
  timedelta(const timedelta& other);

  static timedelta min() { return timedelta(-MAX_DELTA_DAYS); }
  static timedelta max() {
    return timedelta(MAX_DELTA_DAYS, 59, 99999, 0, 59, 23, 0);
  }
  static timedelta resolution() { return timedelta(0, 0, 1); }

  long total_seconds() const;

  operator bool() const {
    return days_ != 0 || seconds_ != 0 || microseconds_ != 0;
  }

  timedelta& operator=(const timedelta& rhs);
  timedelta operator+(const timedelta& rhs) const;
  timedelta& operator+=(const timedelta& rhs);
  timedelta operator-(const timedelta& rhs) const;
  timedelta& operator-=(const timedelta& rhs);
  timedelta operator/(const timedelta& rhs) const;
  timedelta& operator/=(const timedelta& rhs);
  timedelta operator%(const timedelta& rhs) const;
  timedelta& operator%=(const timedelta& rhs);

  bool operator==(const timedelta& rhs) const { return cmp(rhs) == 0; }
  bool operator!=(const timedelta& rhs) const { return !(*this == rhs); }
  bool operator>(const timedelta& rhs) const { return cmp(rhs) > 0; }
  bool operator>=(const timedelta& rhs) const { return cmp(rhs) >= 0; }
  bool operator<(const timedelta& rhs) const { return cmp(rhs) < 0; }
  bool operator<=(const timedelta& rhs) const { return cmp(rhs) <= 0; }

  timedelta operator+() const;
  timedelta operator-() const;

  timedelta operator*(int n) const;
  timedelta& operator*=(int n);
  timedelta operator/(int n) const;
  timedelta& operator/=(int n);
  friend timedelta operator*(int lhs, const timedelta& rhs);

  int days() const { return days_; }
  int seconds() const { return seconds_; }
  int microseconds() const { return microseconds_; }

  timedelta abs() const;
  std::string str() const;
  std::string repr() const;

 private:
  timedelta(int days, int seconds, int microseconds, detail::NotNormalizeTag);

  void set_days(int days) { days_ = days; }
  void set_seconds(int seconds) { seconds_ = seconds; }
  void set_microseconds(int microseconds) { microseconds_ = microseconds; }

  static timedelta microseconds_to_delta(long us);
  long delta_to_microseconds() const;

  int cmp(const timedelta& rhs) const;

 private:
  friend class date;

  int days_ = 0;
  int seconds_ = 0;
  int microseconds_ = 0;
};

class date {
 public:
  date(int year, int month, int day);

  static date today();
  static date fromisoformat(const std::string& date_string);
  static date fromtimestamp(time_t timestamp);
  static date fromordinal(int ordinal);

  static date min() { return date(MINYEAR, 1, 1, detail::NotCheckArgsTag{}); }
  static date max() { return date(MAXYEAR, 12, 31, detail::NotCheckArgsTag{}); }

  static timedelta resolution() { return timedelta(1); }

  int year() const {
    return (static_cast<int>(data_[0]) << 8) | static_cast<int>(data_[1]);
  }
  int month() const { return static_cast<int>(data_[2]); }
  int day() const { return static_cast<int>(data_[3]); }
  int weekday() const;

  bool operator==(const date& rhs) const { return cmp(rhs) == 0; }
  bool operator!=(const date& rhs) const { return cmp(rhs) != 0; }
  bool operator>(const date& rhs) const { return cmp(rhs) > 0; }
  bool operator>=(const date& rhs) const { return cmp(rhs) >= 0; }
  bool operator<(const date& rhs) const { return cmp(rhs) < 0; }
  bool operator<=(const date& rhs) const { return cmp(rhs) <= 0; }

  date operator+(const timedelta& delta) const;
  date& operator+=(const timedelta& delta);
  date operator-(const timedelta& delta) const;
  date& operator-=(const timedelta& delta);
  timedelta operator-(const date& rhs) const;

  std::string ctime() const;
  std::string isoformat() const;

  std::string str() const;
  std::string repr() const;

 private:
  date(int year, int month, int day, detail::NotCheckArgsTag);

  void set_year(int year) {
    data_[0] = static_cast<unsigned char>((year & 0xff00) >> 8);
    data_[1] = static_cast<unsigned char>(year & 0x00ff);
  }
  void set_month(int month) { data_[2] = static_cast<unsigned char>(month); }
  void set_day(int day) { data_[3] = static_cast<unsigned char>(day); }

  void set_fileds(int year, int month, int day) {
    set_year(year);
    set_month(month);
    set_day(day);
  }

  int cmp(const date& rhs) const;

 private:
  friend class datetime;

  unsigned char data_[4];
};

class time {
 public:
  time(int hour, int minute, int second, int usecond);

  static time min() { return time(0, 0, 0, 0, detail::NotCheckArgsTag{}); }
  static time max() {
    return time(23, 59, 59, 999999, detail::NotCheckArgsTag{});
  }

  static timedelta resolution() { return timedelta(0, 0, 1); }

  int hour() const { return static_cast<int>(data_[0]); }
  int minute() const { return static_cast<int>(data_[1]); }
  int second() const { return static_cast<int>(data_[2]); }
  int microsecond() const {
    return (static_cast<int>(data_[3]) << 16) |
           (static_cast<int>(data_[4]) << 8) | static_cast<int>(data_[5]);
  }

  operator bool() const {
    return *reinterpret_cast<const uint32_t*>(data_) != 0 ||
           *reinterpret_cast<const uint16_t*>(data_ + 4) != 0;
  }

  time& operator=(const time& rhs);

  bool operator==(const time& rhs) const { return cmp(rhs) == 0; }
  bool operator!=(const time& rhs) const { return cmp(rhs) != 0; }
  bool operator>(const time& rhs) const { return cmp(rhs) > 0; }
  bool operator>=(const time& rhs) const { return cmp(rhs) >= 0; }
  bool operator<(const time& rhs) const { return cmp(rhs) < 0; }
  bool operator<=(const time& rhs) const { return cmp(rhs) <= 0; }

  std::string isoformat() const;

  std::string str() const;
  std::string repr() const;

 private:
  time(int hour, int minute, int second, int usecond, detail::NotCheckArgsTag);

  void set_hour(int hour) { data_[0] = static_cast<unsigned char>(hour); }
  void set_minute(int minute) { data_[1] = static_cast<unsigned char>(minute); }
  void set_second(int second) { data_[2] = static_cast<unsigned char>(second); }
  void set_microsecond(int microsecond) {
    data_[3] = static_cast<unsigned char>((microsecond & 0xff0000) >> 16);
    data_[4] = static_cast<unsigned char>((microsecond & 0x00ff00) >> 8);
    data_[5] = static_cast<unsigned char>((microsecond & 0x0000ff));
  }

  int cmp(const time& rhs) const;

 private:
  friend class datetime;

  unsigned char data_[6];
};

class datetime {
 public:
  datetime(int year, int month, int day, int hour = 0, int minute = 0,
           int second = 0, int usecond = 0);
  datetime(const datetime& other);

  static datetime now();
  static datetime fromtimestamp(time_t timestamp, time_t us = 0);

  static datetime min() {
    return datetime(MINYEAR, 1, 1, 0, 0, 0, 0, detail::NotCheckArgsTag{});
  }
  static datetime max() {
    return datetime(MAXYEAR, 12, 31, 23, 59, 59, 999999,
                    detail::NotCheckArgsTag{});
  }

  static timedelta resolution() { return timedelta(0, 0, 1); }

  bool operator==(const datetime& rhs) const { return cmp(rhs) == 0; }
  bool operator!=(const datetime& rhs) const { return cmp(rhs) != 0; }
  bool operator>(const datetime& rhs) const { return cmp(rhs) > 0; }
  bool operator>=(const datetime& rhs) const { return cmp(rhs) >= 0; }
  bool operator<(const datetime& rhs) const { return cmp(rhs) < 0; }
  bool operator<=(const datetime& rhs) const { return cmp(rhs) <= 0; }

  datetime& operator=(const datetime& rhs);
  datetime operator+(const timedelta& delta) const;
  datetime& operator+=(const timedelta& delta);
  datetime operator-(const timedelta& delta) const;
  datetime& operator-=(const timedelta& delta);

  timedelta operator-(const datetime& rhs) const;

  ::datetime::date date() const {
    return ::datetime::date(year(), month(), day(), detail::NotCheckArgsTag{});
  }
  ::datetime::time time() const {
    return ::datetime::time(hour(), minute(), second(), microsecond());
  }

  int year() const {
    return (static_cast<int>(data_[0]) << 8) | static_cast<int>(data_[1]);
  }
  int month() const { return static_cast<int>(data_[2]); }
  int day() const { return static_cast<int>(data_[3]); }
  int hour() const { return static_cast<int>(data_[4]); }
  int minute() const { return static_cast<int>(data_[5]); }
  int second() const { return static_cast<int>(data_[6]); }
  int microsecond() const {
    return (static_cast<int>(data_[7]) << 16) |
           (static_cast<int>(data_[8]) << 8) | static_cast<int>(data_[9]);
  }

  std::string ctime() const;

  std::string str() const;
  std::string repr() const;

 private:
  datetime(int year, int month, int day, int hour, int minute, int second,
           int usecond, detail::NotCheckArgsTag);

  void set_year(int year) {
    data_[0] = static_cast<unsigned char>((year & 0xff00) >> 8);
    data_[1] = static_cast<unsigned char>(year & 0x00ff);
  }
  void set_month(int month) { data_[2] = static_cast<unsigned char>(month); }
  void set_day(int day) { data_[3] = static_cast<unsigned char>(day); }
  void set_hour(int hour) { data_[4] = static_cast<unsigned char>(hour); }
  void set_minute(int minute) { data_[5] = static_cast<unsigned char>(minute); }
  void set_second(int second) { data_[6] = static_cast<unsigned char>(second); }
  void set_microsecond(int microsecond) {
    data_[7] = static_cast<unsigned char>((microsecond & 0xff0000) >> 16);
    data_[8] = static_cast<unsigned char>((microsecond & 0x00ff00) >> 8);
    data_[9] = static_cast<unsigned char>((microsecond & 0x0000ff));
  }

  int cmp(const datetime& rhs) const;

 private:
  unsigned char data_[10];
};

inline timedelta operator*(int lhs, const timedelta& rhs) { return rhs * lhs; }

}  // namespace datetime

#endif  // DATETIME_H_
