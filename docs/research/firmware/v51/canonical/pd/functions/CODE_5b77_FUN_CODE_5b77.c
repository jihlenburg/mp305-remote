/* Address: CODE:5b77; name: FUN_CODE_5b77; body bytes: 188 */

void FUN_CODE_5b77(byte param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  undefined1 uVar6;
  
  cVar2 = (0xf < DAT_INTMEM_b2) << 7;
  if (DAT_INTMEM_b2 != 0x10) {
    FUN_CODE_a6a8(6);
    if (-1 < cVar2) {
      FUN_CODE_a7b3();
      if (-1 < cVar2) {
        return;
      }
      bVar1 = FUN_CODE_5c33();
      if (bVar1 == 0) {
        bVar1 = param_1 ^ 2;
      }
      if (bVar1 == 0) {
        FUN_CODE_a63f(0x1c);
        cVar5 = '\0';
        cVar4 = '0';
        FUN_CODE_9a0d();
        if (cVar5 == '\0' && cVar4 == '\0') {
          FUN_CODE_a153();
          if (cVar2 < '\0') {
            uVar6 = 0x3c;
          }
          else {
            uVar6 = 0x34;
          }
        }
        else {
          FUN_CODE_a153();
          if (cVar2 < '\0') {
            uVar6 = 0x3b;
          }
          else {
            uVar6 = 0x32;
          }
        }
      }
      else {
        uVar6 = 0x33;
      }
      FUN_CODE_a03c(uVar6);
      return;
    }
    bVar1 = 0;
    FUN_CODE_9a23(0x80);
    bVar3 = FUN_CODE_5c33();
    if (bVar3 == 0) {
      bVar3 = bVar1 ^ 2;
    }
    if (bVar3 == 0) {
      cVar2 = '\x10';
      FUN_CODE_9a0d();
      if (cVar2 != '\x10' || bVar3 != 0) {
        return;
      }
    }
    goto LAB_CODE_5c29;
  }
  if (DAT_INTMEM_b4 == '2') {
LAB_CODE_5b9d:
    bVar3 = 0;
    bVar1 = 0x20;
    FUN_CODE_9a0d();
    if (bVar3 == 0) {
      bVar3 = bVar1 ^ 0x20;
    }
    if (bVar3 == 0) goto LAB_CODE_5c29;
  }
  else if (DAT_INTMEM_b4 != '4') {
    if (DAT_INTMEM_b4 == ';') goto LAB_CODE_5b9d;
    if (DAT_INTMEM_b4 != '<') {
      if (DAT_INTMEM_b4 != '3') {
        return;
      }
      FUN_CODE_a63f(0x1c);
      return;
    }
  }
  FUN_CODE_9a23(0,0x10);
  cVar4 = -0x80;
  cVar2 = '\0';
  FUN_CODE_9a0d();
  if (cVar4 != -0x80 || cVar2 != '\0') {
    return;
  }
LAB_CODE_5c29:
  FUN_CODE_90d1(0x3b,0x90);
  return;
}

