/* Address: 00053cf4; name: FUN_00053cf4; body bytes: 376 */

void FUN_00053cf4(void)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (((((DAT_1ffe0330 == DAT_1ffe0468) || (DAT_1ffe0330 == DAT_1ffe068c)) ||
       (DAT_1ffe0330 == DAT_1ffe06a0)) || (DAT_1ffe0330 == DAT_1ffe06b4)) &&
     ((DAT_1ffe0330 != DAT_1ffe06a0 || (DAT_1fffab10 == '\0')))) {
    if (DAT_1ffe0330 == DAT_1ffe0468) {
      FUN_00018114(DAT_1ffe0348);
      uVar3 = 6;
      goto LAB_00053e5a;
    }
    FUN_00018114(DAT_1ffe0348);
  }
  else {
    if (DAT_1ffe0330 == DAT_1ffe03c8) {
      uVar3 = DAT_1ffe03d8;
      if (((DAT_1fffab03 != '\0') && (DAT_1fffaad6 != '\0')) ||
         ((DAT_1fffab04 != '\0' && (DAT_1fffaad7 != '\0')))) {
LAB_00053e36:
        FUN_00018114(uVar3);
      }
    }
    else if (DAT_1ffe0330 == DAT_1ffe06c8) {
      FUN_00017aa4();
    }
    else if (DAT_1ffe0330 == DAT_1ffe06d0) {
      FUN_000180c4();
    }
    else if (DAT_1ffe0330 == DAT_1ffe06d8) {
      FUN_00017e74();
    }
    else if (DAT_1ffe0330 == DAT_1ffe06e0) {
      FUN_00017f28();
    }
    else if (DAT_1ffe0330 == DAT_1ffe06e8) {
      FUN_00017d9c();
    }
    else if (DAT_1ffe0330 == DAT_1ffe06f8) {
      FUN_00018010();
    }
    else if (DAT_1ffe0330 == DAT_1ffe06f0) {
      FUN_00017ca8();
    }
    else if (DAT_1ffe0330 == DAT_1ffe0450) {
      FUN_00018114(DAT_1ffe0348);
      uVar3 = FUN_0004b9de(DAT_1ffe0454,1);
      iVar2 = FUN_0004cd84(uVar3,1);
      uVar1 = DAT_1ffe023e;
      if (iVar2 != 0) {
        uVar1 = DAT_1ffe023f;
      }
      uVar3 = FUN_0004b9de(DAT_1ffe0458,uVar1);
      FUN_0004e4b2(uVar3,0);
    }
    else if (DAT_1ffe0330 == DAT_1ffe0634) {
      FUN_00017a54();
    }
    else if (DAT_1ffe0330 == DAT_1ffe063c) {
      FUN_00017af4();
    }
    else if (DAT_1ffe0330 == DAT_1ffe0644) {
      FUN_0001799c();
    }
    else if (DAT_1ffe0330 == DAT_1ffe064c) {
      FUN_00017b44();
    }
    else {
      uVar3 = DAT_1ffe0348;
      if ((DAT_1ffe0330 == DAT_1ffe0738) || (DAT_1ffe0330 == DAT_1ffe075c)) goto LAB_00053e36;
    }
    FUN_0004aa4c(DAT_1ffe0330,0x58485,7,0);
  }
  uVar3 = 0xf;
LAB_00053e5a:
  FUN_0001cb8c(uVar3);
  DAT_1ffe02b4 = 0;
  DAT_1ffe0247 = 1;
  DAT_1ffe0248 = 0;
  return;
}

