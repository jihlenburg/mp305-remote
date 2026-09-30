/* Address: 0005f96c; name: FUN_0005f96c; body bytes: 248 */

void FUN_0005f96c(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  
  if (((DAT_1fffab03 != '\0') && (DAT_1fffaad6 != '\0')) ||
     ((DAT_1fffab04 != '\0' && (DAT_1fffaad7 != '\0')))) {
    iVar1 = FUN_00046688(param_1);
    uVar2 = FUN_00050710(DAT_1ffe03d8);
    cVar5 = DAT_1fffaae2;
    if (DAT_1fffaad7 != '\0') {
      cVar5 = DAT_1fffaae3;
    }
    if ((iVar1 == 0xe) && (DAT_1ffe0245 == '\0')) {
      iVar1 = FUN_00046700(param_1);
      uVar4 = uVar2;
      if (iVar1 == 0x1c) {
        FUN_0005833c(uVar2 & 0xffff);
        FUN_0004e5a6(DAT_1ffe0330,7,0);
      }
      else if (iVar1 == 0x1d) {
        if (cVar5 == '\0') {
          if (DAT_1fffaad7 == '\0') {
            cVar5 = '\x02';
          }
          else {
            cVar5 = '\x03';
          }
        }
        else {
          cVar5 = cVar5 + -1;
        }
        FUN_0001cb8c(0xf);
      }
      else {
        iVar1 = iVar1 + -100;
        if (cVar5 == '\x03') {
          uVar3 = uVar2 + iVar1 * 1000;
        }
        else if (cVar5 == '\x02') {
          uVar3 = uVar2 + iVar1 * 100;
        }
        else if (cVar5 == '\x01') {
          uVar3 = uVar2 + iVar1 * 10;
        }
        else {
          uVar3 = uVar2 + iVar1;
        }
        uVar4 = uVar3;
        if ((((DAT_1fffaad6 != '\0') && ((int)uVar2 < (int)uVar3)) &&
            ((cVar5 == '\x03' || (cVar5 == '\x02')))) &&
           ((uVar4 = uVar2, (int)uVar2 < 3000 && (uVar4 = uVar3, 2999 < (int)uVar3)))) {
          uVar4 = 3000;
        }
      }
      FUN_00056c2c(uVar4,cVar5);
    }
    DAT_1ffe02b4 = 0;
  }
  return;
}

