/* Address: CODE:4e91; name: FUN_CODE_4e91; body bytes: 267 */

void FUN_CODE_4e91(byte param_1,byte param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  byte bVar3;
  undefined2 uVar4;
  
  DAT_EXTMEM_04aa = param_1;
  DAT_EXTMEM_04ab = param_2;
  FUN_CODE_a595();
  FUN_CODE_7d84(0,0x4ac);
  FUN_CODE_87aa(0x40,0xb5);
  bVar3 = DAT_EXTMEM_04aa;
  if (DAT_EXTMEM_04aa == 0) {
    bVar3 = DAT_EXTMEM_04ab ^ 0x13;
  }
  if (bVar3 == 0) {
    uVar2 = 0xb5;
    uVar1 = 0x43;
    uVar4 = 0x4ac;
  }
  else {
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 2;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 5;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x2d;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x33;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0xc;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x37;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x34;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x32;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x2c;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x30;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    uVar2 = 0xb4;
    uVar1 = 0x40;
    uVar4 = 0x4aa;
  }
  FUN_CODE_7d6d(uVar4,uVar1,uVar2,0xff);
LAB_CODE_4f93:
  FUN_CODE_87aa();
  FUN_CODE_7d98();
  FUN_CODE_87aa();
  return;
}

