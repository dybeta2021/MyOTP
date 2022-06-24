#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : python 
# @File     : test.py 
# @Author   : yangdong
# @Time     : 2022/6/18 00:22

from os import getcwd, sep, makedirs, mkdir
from os.path import exists
from app_yijinjing_service import run_page_service

folder =  getcwd() + sep + r"yjj"
journal_folder = getcwd() + sep + r"yjj" + sep + r"journal" + sep

if not exists(folder):
    mkdir(folder)

if not exists(journal_folder):
    mkdir(journal_folder)

log_file = r"clogs/yjj_service.log"
run_page_service(log_file=log_file, journal_folder=journal_folder)