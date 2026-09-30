/* Address: 0001e7b4; name: FUN_0001e7b4; body bytes: 1140 */

void FUN_0001e7b4(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  if (DAT_1ffe0243 == '\0') {
    if ((((DAT_1ffe0247 != '\0') && (DAT_1ffe0330 != DAT_1ffe0468)) &&
        (DAT_1ffe0330 != DAT_1ffe0550)) &&
       ((DAT_1ffe0330 != DAT_1ffe03c8 &&
        (DAT_1ffe02b4 = DAT_1fffab60 + DAT_1ffe02b4, 59999 < DAT_1ffe02b4)))) {
      DAT_1ffe02b4 = 0;
      FUN_0001ba58();
    }
  }
  else {
    DAT_1ffe02b0 = DAT_1fffab60 + DAT_1ffe02b0;
    if (3000 < DAT_1ffe02b0) {
      FUN_0001814c();
      FUN_00018114(DAT_1ffe0348);
    }
  }
  iVar1 = FUN_0004cd1e(DAT_1ffe0700);
  if ((iVar1 == 0) && (DAT_1ffe02b8 = DAT_1fffab60 + DAT_1ffe02b8, 2000 < DAT_1ffe02b8)) {
    DAT_1ffe02b8 = 0;
    DAT_1fff9550 = DAT_1fff9550 | 0x10;
  }
  if ((DAT_1fffaae5 < 4) && (iVar1 = FUN_0004fe9c(), iVar1 != DAT_1ffe0590)) {
    FUN_0004fea8();
    if (DAT_1ffe02c4 == 0) {
      DAT_1ffe02c4 = FUN_0005285c(0x5889d,100,0);
      FUN_00052a82();
    }
    FUN_0001bae4();
    FUN_0001814c();
    DAT_1fffaacd = 0;
    FUN_0001a5fc();
  }
  else if ((DAT_1fffaae5 - 7 < 3) && ((remote_granted != '\0' && (DAT_1fffab0c == '\0')))) {
    DAT_1fffab0c = '\x01';
    iVar1 = FUN_0004cd1e(DAT_1ffe05a8);
    if ((iVar1 == 0) || (iVar1 = FUN_0004cd1e(DAT_1ffe04c8), iVar1 == 0)) {
LAB_0001e8ee:
      FUN_0001bae4();
    }
    else if (DAT_1ffe04f4 == 0) {
      if (DAT_1ffe05b8 != 0) {
        iVar1 = FUN_0004cd1e(DAT_1ffe0614);
        uVar3 = DAT_1ffe0608;
        if (iVar1 == 0) goto LAB_0001e8ee;
        goto LAB_0001e8e8;
      }
      if (DAT_1ffe0620 != 0) {
        puVar2 = &DAT_1ffe0680;
        goto LAB_0001e8e6;
      }
    }
    else {
      puVar2 = &DAT_1ffe0540;
LAB_0001e8e6:
      uVar3 = *puVar2;
LAB_0001e8e8:
      iVar1 = FUN_0004cd1e(uVar3);
      if (iVar1 == 0) goto LAB_0001e8ee;
    }
    if ((DAT_1ffe0330 != 0) && (DAT_1ffe0330 != DAT_1ffe06a0)) {
      FUN_0001ba58();
    }
  }
  if (DAT_1fffaae0 == '\0') goto LAB_0001ea42;
  DAT_1fffaae0 = '\0';
  FUN_00013f24();
  if (DAT_1fffab17 == '\x01') goto LAB_0001ea3a;
  iVar1 = FUN_0004cd1e(DAT_1ffe0700);
  if (iVar1 == 0) {
    puVar2 = &DAT_1ffe0704;
    goto LAB_0001ec52;
  }
  iVar1 = FUN_0004cd1e(DAT_1ffe072c);
  if (iVar1 == 0) {
    iVar1 = FUN_0004cd84(DAT_1ffe0730,1);
    uVar3 = DAT_1ffe0730;
    if (iVar1 != 0) goto LAB_0001ea3a;
LAB_0001e9da:
    FUN_0004e5a6(uVar3,7,0);
  }
  else {
    iVar1 = FUN_0004cd1e(DAT_1ffe071c);
    if (iVar1 == 0) {
      puVar2 = &DAT_1ffe0720;
LAB_0001ec52:
      uVar3 = *puVar2;
      goto LAB_0001e9da;
    }
    iVar1 = FUN_0004cd1e(DAT_1ffe04c8);
    if (iVar1 == 0) {
      puVar2 = &DAT_1ffe04d0;
      goto LAB_0001ec52;
    }
    if (DAT_1ffe04f4 == 0) {
      if (DAT_1ffe05b8 == 0) {
        if ((DAT_1ffe0620 == 0) || (iVar1 = FUN_0004cd1e(DAT_1ffe0680), iVar1 != 0))
        goto LAB_0001e9c8;
        puVar2 = &DAT_1ffe0684;
      }
      else {
        iVar1 = FUN_0004cd1e(DAT_1ffe0614);
        if (iVar1 == 0) {
          puVar2 = &DAT_1ffe0618;
        }
        else {
          iVar1 = FUN_0004cd1e(DAT_1ffe0608);
          if (iVar1 != 0) goto LAB_0001e9c8;
          puVar2 = &DAT_1ffe060c;
        }
      }
      goto LAB_0001ec52;
    }
    iVar1 = FUN_0004cd1e(DAT_1ffe0540);
    if (iVar1 == 0) {
      puVar2 = &DAT_1ffe0544;
      goto LAB_0001ec52;
    }
LAB_0001e9c8:
    if (DAT_1ffe0330 == 0) {
      iVar1 = FUN_0004cd1e(DAT_1ffe05a8);
      if ((iVar1 != 0) && (remote_granted == '\0')) {
        FUN_0004e5a6(DAT_1ffe03bc,7,0);
        DAT_1ffe0245 = 0;
        goto LAB_0001ea3a;
      }
      if (((DAT_1ffe0330 == 0) && (remote_granted == '\x01')) &&
         (iVar1 = FUN_0004cd1e(DAT_1ffe06a0), iVar1 != 0)) {
        puVar2 = &DAT_1ffe03c4;
        goto LAB_0001ec52;
      }
    }
    if (DAT_1ffe0247 == '\0') {
      iVar1 = FUN_0004cd1e(DAT_1ffe05a8);
      if (iVar1 == 0) {
        puVar2 = &DAT_1ffe05ac;
        goto LAB_0001ec52;
      }
    }
    else {
      FUN_0001ba58();
    }
  }
LAB_0001ea3a:
  DAT_1fffab88 = 0;
  DAT_1fffab8c = 0;
LAB_0001ea42:
  FUN_00036048();
  FUN_000128a4();
  FUN_000127fc();
  FUN_00012adc();
  FUN_000126b8();
  FUN_00054818(DAT_1fffab22);
  FUN_00055940(DAT_1fffab6a);
  FUN_0005472c(DAT_1fffaca8);
  service_bind_prompt();
  FUN_0005553c(remote_request);
  FUN_00055854(DAT_1fffab0b);
  FUN_0005486c(DAT_1fffaada);
  FUN_00055158(DAT_1fffaace);
  FUN_00054cec(DAT_1fffaace);
  FUN_00057ea0(DAT_1fffaace,0);
  FUN_000558b0(DAT_1fffaadc);
  FUN_00057064(DAT_1fffaae4,0);
  FUN_00056d80(DAT_1fffaade);
  FUN_00055ec8(DAT_1fffaacf);
  FUN_000571b0(DAT_1fffaad0);
  FUN_00057314(DAT_1fffaafe);
  FUN_000553c8(DAT_1fffab78);
  FUN_00054e80(DAT_1fffab78);
  FUN_000557e4(DAT_1fffab78);
  FUN_00055040(DAT_1fffab7a);
  FUN_00054c38(DAT_1fffab7a);
  FUN_00055684(DAT_1fffab7a);
  FUN_000550e8(DAT_1fffab7c);
  FUN_00054c98(DAT_1fffab7c);
  FUN_000556f4(DAT_1fffab7c);
  FUN_00055340(DAT_1fffab9c);
  FUN_00055774(DAT_1fffab9c);
  FUN_00054fd8(DAT_1fffaba0);
  FUN_00055630(DAT_1fffaba0);
  FUN_00057740(DAT_1fffaaeb);
  FUN_00057c18(DAT_1fffaaf7);
  FUN_00055ab0(DAT_1fffab06);
  FUN_00055d8c(DAT_1fffab4e,DAT_1fffab4c);
  FUN_00055e04((undefined2)DAT_1fffa128);
  FUN_00055e30(DAT_1fffab98);
  FUN_00055e90((int)DAT_1fffab05);
  FUN_00055a88(DAT_1fffab4a);
  FUN_00055a54(DAT_1ffe032c);
  FUN_00056244();
  FUN_0005f060();
  FUN_00054474(requested_mode);
  FUN_00057d54();
  if (DAT_1ffe0554 != 0) {
    if (DAT_1fffaad8 != '\0') {
      DAT_1ffe02e8 = 0;
      FUN_000568f4();
    }
    if (DAT_1ffe024b - 1 < 7) {
      DAT_1ffe02e8 = DAT_1fffab60 + DAT_1ffe02e8;
      if (14999 < DAT_1ffe02e8) {
        DAT_1ffe02e8 = 0;
        DAT_1ffe024b = 0;
      }
    }
    else {
      DAT_1ffe02e8 = 0;
    }
  }
  if (DAT_1ffe0448 != 0) {
    if (DAT_1fffaad9 == '\0') {
      DAT_1ffe02f0 = 0;
      DAT_1ffe026b = '\0';
    }
    else {
      DAT_1ffe02ec = 0;
      DAT_1ffe02f0 = DAT_1fffab60 + DAT_1ffe02f0;
      if ((4999 < DAT_1ffe02f0) && (DAT_1ffe026b == '\0')) {
        uVar3 = FUN_0004b9de(DAT_1ffe0448,1);
        FUN_0004e00e(uVar3,1);
        DAT_1ffe026b = '\x01';
      }
    }
    if (DAT_1ffe024c - 1 < 7) {
      DAT_1ffe02ec = DAT_1fffab60 + DAT_1ffe02ec;
      if (14999 < DAT_1ffe02ec) {
        DAT_1ffe02ec = 0;
        DAT_1ffe024c = 0;
      }
    }
    else {
      DAT_1ffe02ec = 0;
    }
  }
  return;
}

