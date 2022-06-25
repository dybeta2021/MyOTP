#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : python 
# @File     : run_service.py 
# @Author   : 稻草人
# @Time     : 2022/6/18 16:04

from os import getcwd, sep, mkdir
from os.path import exists
from core.api.shmipc.app_yijinjing_service import run_page_service

folder = getcwd() + sep + r"access"
journal_folder = getcwd() + sep + r"access" + sep + r"journal" + sep

if not exists(folder):
    mkdir(folder)

if not exists(journal_folder):
    mkdir(journal_folder)

log_file = r"clogs/yjj_paged_service.log"
run_page_service(log_file=log_file, journal_folder=journal_folder)
