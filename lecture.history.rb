#!/usr/bin/env ruby -wKU

arr = [
  16,      # 1:21-22, 한동대 코딩캠프
  8,       # 3:2, interpol
  24,      # 5:18-20, 대검심화
  48,      # 5:31-6:11, 인도네시아
  8,       # 6:16, 국보
  16,      # 7:4,7, 싱가폴 MOM
  4,       # 7:13, 한아세안
  6,       # 8:4-5, 한아세안, 캄보디아
  16,      # 8:9-10, 경찰청
  8,       # 8:22, 사우디 
  24,      # 8:29-31, 경찰청 심화
  8,       # 9:19, 홍콩 HKPF
  8,       # 9:21, 모바일 심화
  24,      # 10:19-21, 관세청 심화
  8,       # 10:25 홍콩 IMMD, 방글라데시 BCC
  24,      # 10:26-28, 경찰청 심화
  2,       # 11:2, 한림대 특강 및 회사소개
  16,      # 11:7,9 몽고 교육
  16,      # 11:10,11, 조사본부 심화
  8,       # 11:14, 사우디, 인니
  8,       # 11:15, 경찰청 심호
  12,      # 11:21,22, TTT
  8,       # 12:5, 홍콩
  1        # 12:27, 형사국
]

p arr.reduce(:+)