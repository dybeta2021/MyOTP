## Quote-Engine

CTP行情接口，行情刷新引擎

### SPSC/SPMC
使用开源版本的yijinjing数据库实现多进程无锁一写多读

### MPMC/MPSC
- 使用OptimistAtomicQueue + yijinjing组合实现一个进程multi-producer，多个进程multi-consumer结构
- 使用Disruptor实现一个进程multi-producer另一个进程multi-consumer的结构