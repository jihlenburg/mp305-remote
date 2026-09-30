/* Address: 000607d8; name: FUN_000607d8; body bytes: 6396 */

void FUN_000607d8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 uVar7;
  
  if ((*(byte *)(param_1 + 0x24) & 1) == 0) {
    uVar2 = FUN_0004f010(0x12,4,param_3,param_4,param_3,param_4);
  }
  else {
    uVar2 = FUN_0004037c(0x15171a);
  }
  *(short *)(param_1 + 0x30) = (short)uVar2;
  *(char *)(param_1 + 0x32) = (char)((uint)uVar2 >> 0x10);
  if ((*(byte *)(param_1 + 0x24) & 1) == 0) {
    uVar2 = FUN_0004efd0(0x12,4);
  }
  else {
    uVar2 = FUN_0004f010(0x12,5);
  }
  *(short *)(param_1 + 0x33) = (short)uVar2;
  *(char *)(param_1 + 0x35) = (char)((uint)uVar2 >> 0x10);
  if ((*(byte *)(param_1 + 0x24) & 1) == 0) {
    uVar2 = FUN_0004059e();
  }
  else {
    uVar2 = FUN_0004037c(0x282b30);
  }
  *(short *)(param_1 + 0x36) = (short)uVar2;
  *(char *)(param_1 + 0x38) = (char)((uint)uVar2 >> 0x10);
  if ((*(byte *)(param_1 + 0x24) & 1) == 0) {
    uVar2 = FUN_0004f010(0x12,2);
  }
  else {
    uVar2 = FUN_0004037c(0x2f3237);
  }
  *(short *)(param_1 + 0x39) = (short)uVar2;
  *(char *)(param_1 + 0x3b) = (char)((uint)uVar2 >> 0x10);
  FUN_000620f0();
  FUN_000620f0();
  FUN_00051038(param_1 + 0x374,&DAT_00082ce0,0x3ca99,0x50,0x46,0);
  iVar3 = param_1 + 0x388;
  uVar7 = 0;
  uVar2 = 0;
  FUN_00051038(iVar3,&DAT_00082ce0,0x3ca99,0x50,0);
  FUN_00051026(param_1 + 0x184,param_1 + 0x374);
  FUN_00051026(param_1 + 400,iVar3);
  iVar4 = param_1 + 0x4c;
  FUN_000620f0();
  if ((*(byte *)(param_1 + 0x24) & 1) == 0) {
    uVar5 = FUN_0004f04c(0x12);
  }
  else {
    uVar5 = FUN_0004efd0(0x12,2);
  }
  FUN_00050d1e(iVar4,uVar5);
  FUN_00050f7c(iVar4,0x7fff);
  iVar6 = *(int *)(param_1 + 0x2c) * 7 + 0x50;
  if (iVar6 < 0x140) {
    iVar6 = 1;
  }
  else {
    iVar6 = iVar6 / 0xa0;
  }
  FUN_00050e5a(iVar4,iVar6);
  iVar6 = *(int *)(param_1 + 0x2c) * 5 + 0x50;
  if (iVar6 < 0x140) {
    iVar6 = 1;
  }
  else {
    iVar6 = iVar6 / 0xa0;
  }
  FUN_0005102e(iVar4,iVar6);
  FUN_00050d62(iVar4,0x66);
  FUN_00051026(iVar4,iVar3);
  FUN_000620f0();
  FUN_00050d62(param_1 + 0x58,0xff);
  iVar3 = param_1 + 0x40;
  FUN_000620f0();
  FUN_00050d62(iVar3,0xff);
  FUN_00050d1e(iVar3,*(undefined4 *)(param_1 + 0x30));
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050fe8(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  FUN_00051006(iVar3,*(undefined4 *)(param_1 + 0x1c));
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ecc(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e88(iVar3,iVar4);
  FUN_00050f84(iVar3,((int)(*(int *)(param_1 + 0x2c) +
                           ((uint)(*(int *)(param_1 + 0x2c) >> 0x1f) >> 0x1e)) >> 2) << 8);
  iVar3 = param_1 + 100;
  FUN_000620f0();
  if (*(char *)(param_1 + 0x28) == '\x01') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 8;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (*(char *)(param_1 + 0x28) == '\x01') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 8;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050f7c(iVar3,iVar4);
  FUN_00050d62(iVar3,0xff);
  FUN_00050d1e(iVar3,*(undefined4 *)(param_1 + 0x36));
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x39));
  FUN_00050d6a(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  iVar4 = *(int *)(param_1 + 0x2c) * 2 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050da0(iVar3,iVar4);
  FUN_00050d90(iVar3,1);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050fe8(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0x18;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0x14;
  }
  else {
    iVar4 = 0x10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0x18;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0x14;
    }
    else {
      iVar4 = 0x10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e5a(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ecc(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e88(iVar3,iVar4);
  uVar5 = FUN_0004f04c(0x12);
  FUN_00050dd0(iVar3,uVar5);
  iVar4 = *(int *)(param_1 + 0x2c) + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050dee(iVar3,iVar4);
  iVar3 = param_1 + 0x130;
  FUN_000620f0();
  FUN_00050dfe(iVar3,*(undefined4 *)(param_1 + 0x10));
  iVar4 = *(int *)(param_1 + 0x2c) * 3 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050e2c(iVar3,iVar4);
  iVar4 = *(int *)(param_1 + 0x2c) * 3 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050e24(iVar3,iVar4);
  FUN_00050e1c(iVar3,0x7f);
  iVar3 = param_1 + 0x13c;
  FUN_000620f0();
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x13));
  FUN_00050dfe(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  iVar4 = *(int *)(param_1 + 0x2c) * 3 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050e2c(iVar3,iVar4);
  FUN_00050e1c(iVar3,0x7f);
  iVar3 = param_1 + 0x70;
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0x10;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 8;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0x10;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 8;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050f7c(iVar3,iVar4);
  FUN_00050d62(iVar3,0xff);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x39));
  FUN_00050d1e(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  if ((*(byte *)(param_1 + 0x24) & 1) == 0) {
    uVar5 = FUN_0004f04c(0x12);
    FUN_00050f8c(iVar3,uVar5);
    iVar4 = FUN_0004089c(0);
    if (iVar4 * 3 + 0x50 < 0x140) {
      iVar4 = 1;
    }
    else {
      iVar4 = FUN_0004089c(0);
      iVar4 = (iVar4 * 3 + 0x50) / 0xa0;
    }
    FUN_00050fc2(iVar3,iVar4);
    FUN_00050fb2(iVar3,0x7f);
    iVar4 = FUN_0004089c(0);
    if ((iVar4 * 4 + 0x50 < 0x140) || (iVar4 = FUN_0004089c(0), (iVar4 * 4 + 0x50) / 0xa0 != 0)) {
      iVar4 = FUN_0004089c(0);
      if (iVar4 * 4 + 0x50 < 0x140) {
        iVar4 = 1;
      }
      else {
        iVar4 = FUN_0004089c(0);
        iVar4 = (iVar4 * 4 + 0x50) / 0xa0;
      }
      if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
        iVar4 = 1;
      }
      else {
        iVar4 = FUN_0004089c(0);
        if (iVar4 * 4 + 0x50 < 0x140) {
          iVar4 = 1;
        }
        else {
          iVar4 = FUN_0004089c(0);
          iVar4 = (iVar4 * 4 + 0x50) / 0xa0;
        }
        iVar4 = (*(int *)(param_1 + 0x2c) * iVar4 + 0x50) / 0xa0;
      }
    }
    else {
      iVar4 = 0;
    }
    FUN_00050faa(iVar3,iVar4);
  }
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050fe8(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0x18;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0x14;
  }
  else {
    iVar4 = 0x10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0x18;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0x14;
    }
    else {
      iVar4 = 0x10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ea6(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050edc(iVar3,iVar4);
  iVar4 = *(int *)(param_1 + 0x2c) * 5 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050e88(iVar3,iVar4);
  iVar4 = *(int *)(param_1 + 0x2c) * 5 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050ecc(iVar3,iVar4);
  FUN_00040310(param_1 + 0x364,0x279c3);
  FUN_00040310(param_1 + 0x36c,0x37ed1);
  FUN_000620f0();
  FUN_00050db0(param_1 + 0xc4,param_1 + 0x364);
  FUN_00050db8(param_1 + 0xc4,0x23);
  FUN_000620f0();
  FUN_00050db0(param_1 + 0xd0,param_1 + 0x36c);
  FUN_00050db8(param_1 + 0xd0,0x7f);
  FUN_000620f0();
  FUN_00050da8(param_1 + 0x160,1);
  FUN_00050d90(param_1 + 0x160,1);
  iVar3 = param_1 + 0x100;
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0x18;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0x14;
  }
  else {
    iVar4 = 0x10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0x18;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0x14;
    }
    else {
      iVar4 = 0x10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e5a(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0x18;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0x14;
  }
  else {
    iVar4 = 0x10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0x18;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0x14;
    }
    else {
      iVar4 = 0x10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ecc(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0x18;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0x14;
  }
  else {
    iVar4 = 0x10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0x18;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0x14;
    }
    else {
      iVar4 = 0x10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e88(iVar3,iVar4);
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar3 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar3 = 0xc;
  }
  else {
    iVar3 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar3 + 0x50 < 0x140) {
    iVar3 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar3 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar3 = 0xc;
    }
    else {
      iVar3 = 10;
    }
    iVar3 = (iVar3 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e5a(param_1 + 0xf4,iVar3);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar3 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar3 = 0xc;
  }
  else {
    iVar3 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar3 + 0x50 < 0x140) {
    iVar3 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar3 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar3 = 0xc;
    }
    else {
      iVar3 = 10;
    }
    iVar3 = (iVar3 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e90(param_1 + 0xf4,iVar3);
  FUN_000620f0();
  iVar3 = *(int *)(param_1 + 0x2c) * 10 + 0x50;
  if (iVar3 < 0x140) {
    iVar3 = 1;
  }
  else {
    iVar3 = iVar3 / 0xa0;
  }
  FUN_00050ecc(param_1 + 0x10c,iVar3);
  iVar3 = *(int *)(param_1 + 0x2c) * 10 + 0x50;
  if (iVar3 < 0x140) {
    iVar3 = 1;
  }
  else {
    iVar3 = iVar3 / 0xa0;
  }
  FUN_00050e88(param_1 + 0x10c,iVar3);
  FUN_000620f0();
  iVar3 = *(int *)(param_1 + 0x2c) * 0x14 + 0x50;
  if (iVar3 < 0x140) {
    iVar3 = 1;
  }
  else {
    iVar3 = iVar3 / 0xa0;
  }
  FUN_0005100e(param_1 + 0x118,iVar3);
  FUN_000620f0();
  FUN_00050fe0(param_1 + 0x124,2);
  iVar3 = param_1 + 0xdc;
  FUN_000620f0();
  FUN_00050e5a(iVar3,0);
  FUN_00050ecc(iVar3,0);
  FUN_00050e88(iVar3,0);
  iVar3 = param_1 + 0xe8;
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 8;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 6;
  }
  else {
    iVar4 = 2;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 8;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 6;
    }
    else {
      iVar4 = 2;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e5a(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 8;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 6;
  }
  else {
    iVar4 = 2;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 8;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 6;
    }
    else {
      iVar4 = 2;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ecc(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 8;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 6;
  }
  else {
    iVar4 = 2;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 8;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 6;
    }
    else {
      iVar4 = 2;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e88(iVar3,iVar4);
  iVar3 = param_1 + 0x7c;
  FUN_000620f0();
  FUN_00050d1e(iVar3,*(undefined4 *)(param_1 + 0x10));
  uVar5 = FUN_0004059e();
  FUN_00050fe8(iVar3,uVar5);
  FUN_00050d62(iVar3,0xff);
  iVar3 = param_1 + 0x88;
  FUN_000620f0();
  FUN_00050d1e(iVar3,*(undefined4 *)(param_1 + 0x10));
  FUN_00050fe8(iVar3,*(undefined4 *)(param_1 + 0x10));
  FUN_00050d62(iVar3,0x33);
  iVar3 = param_1 + 0x94;
  FUN_000620f0();
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x13));
  FUN_00050d1e(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  uVar5 = FUN_0004059e();
  FUN_00050fe8(iVar3,uVar5);
  FUN_00050d62(iVar3,0xff);
  iVar3 = param_1 + 0xa0;
  FUN_000620f0();
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x13));
  FUN_00050d1e(iVar3,uVar5);
  uVar5 = CONCAT13((char)((uint)uVar5 >> 0x18),*(undefined3 *)(param_1 + 0x13));
  FUN_00050fe8(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  FUN_00050d62(iVar3,0x33);
  iVar3 = param_1 + 0xac;
  FUN_000620f0();
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x39));
  FUN_00050d1e(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  FUN_00050d62(iVar3,0xff);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050fe8(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  iVar3 = param_1 + 0xb8;
  FUN_000620f0();
  FUN_00050d1e(iVar3,*(undefined4 *)(param_1 + 0x36));
  FUN_00050d62(iVar3,0xff);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050fe8(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  FUN_000620f0();
  FUN_00050f7c(param_1 + 0x148,0x7fff);
  FUN_000620f0();
  FUN_00050f7c(param_1 + 0x154,0);
  FUN_000620f0();
  FUN_00050f84(param_1 + 0x16c,
               ((int)(*(int *)(param_1 + 0x2c) + ((uint)(*(int *)(param_1 + 0x2c) >> 0x1f) >> 0x1e))
               >> 2) << 8);
  FUN_000620f0();
  iVar3 = *(int *)(param_1 + 0x2c) * 3 + 0x50;
  if (iVar3 < 0x140) {
    iVar3 = 1;
  }
  else {
    iVar3 = iVar3 / 0xa0;
  }
  FUN_0005101e(param_1 + 0x178,iVar3);
  iVar3 = *(int *)(param_1 + 0x2c) * 3 + 0x50;
  if (iVar3 < 0x140) {
    iVar3 = 1;
  }
  else {
    iVar3 = iVar3 / 0xa0;
  }
  FUN_00051016(param_1 + 0x178,iVar3);
  iVar3 = param_1 + 0x1b4;
  FUN_000620f0();
  FUN_00050d1e(iVar3,*(undefined4 *)(param_1 + 0x10));
  FUN_00050d62(iVar3,0xff);
  iVar4 = *(int *)(param_1 + 0x2c) * 6 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050e5a(iVar3,iVar4);
  FUN_00050f7c(iVar3,0x7fff);
  FUN_000620f0();
  FUN_00050ce8(param_1 + 0x19c,200);
  FUN_000620f0();
  FUN_00050ce8(param_1 + 0x1a8,0x78);
  iVar3 = param_1 + 0x1c0;
  FUN_000620f0();
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x39));
  FUN_00050cf0(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  iVar4 = *(int *)(param_1 + 0x2c) * 0xf + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050d16(iVar3,iVar4);
  FUN_00050d0e(iVar3,1);
  FUN_000620f0();
  FUN_00050cf0(param_1 + 0x1cc,*(undefined4 *)(param_1 + 0x10));
  FUN_000620f0();
  FUN_00050df6(param_1 + 0x1fc,0x104);
  iVar3 = param_1 + 0x208;
  FUN_000620f0();
  iVar4 = *(int *)(param_1 + 0x2c) * 3 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050e5a(iVar3,iVar4);
  iVar4 = *(int *)(param_1 + 0x2c) * 2 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050da0(iVar3,iVar4);
  FUN_00050d6a(iVar3,*(undefined4 *)(param_1 + 0x10));
  FUN_00050d1e(iVar3,*(undefined4 *)(param_1 + 0x36));
  FUN_00050d62(iVar3,0xff);
  if (*(char *)(param_1 + 0x28) == '\x01') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 8;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (*(char *)(param_1 + 0x28) == '\x01') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 8;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050f7c(iVar3,iVar4 / 2);
  FUN_00051006(iVar3,*(undefined4 *)(param_1 + 0x18));
  uVar5 = FUN_0004059e();
  FUN_00050fe8(iVar3,uVar5);
  FUN_000620f0();
  FUN_00050d5a(param_1 + 0x214,&DAT_000618dc);
  FUN_000620f0();
  iVar3 = *(int *)(param_1 + 0x2c) * 4 + 0x50;
  if (iVar3 < 0x140) {
    iVar3 = 1;
  }
  else {
    iVar3 = iVar3 / 0xa0;
  }
  FUN_00050e5a(param_1 + 0x220,-iVar3);
  uVar5 = FUN_0004059e();
  FUN_00050d1e(param_1 + 0x220,uVar5);
  FUN_000620f0();
  FUN_00050dee(param_1 + 0x22c,1);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050dd0(param_1 + 0x22c,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  iVar3 = param_1 + 0x1f0;
  FUN_000620f0();
  FUN_00050d90(iVar3,0);
  iVar4 = *(int *)(param_1 + 0x2c) * 10 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050e88(iVar3,iVar4);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x39));
  FUN_00050dd0(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  iVar3 = param_1 + 0x1d8;
  FUN_000620f0();
  iVar4 = *(int *)(param_1 + 0x2c) * 3 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050dee(iVar3,iVar4);
  iVar4 = *(int *)(param_1 + 0x2c) * 3 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050f7c(iVar3,iVar4);
  iVar4 = *(int *)(param_1 + 0x2c) * 8 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050fca(iVar3,iVar4);
  iVar6 = *(int *)(param_1 + 0x2c) * 2 + 0x50;
  if (iVar6 < 0x140) {
    iVar6 = 1;
  }
  else {
    iVar6 = iVar6 / 0xa0;
  }
  FUN_00050e88(iVar3,iVar6);
  iVar3 = param_1 + 0x1e4;
  FUN_000620f0();
  FUN_00050f7c(iVar3,0x7fff);
  FUN_00050fca(iVar3,iVar4);
  FUN_00050d1e(iVar3,*(undefined4 *)(param_1 + 0x10));
  FUN_00050d62(iVar3,0xff);
  iVar3 = param_1 + 0x280;
  FUN_000620f0();
  FUN_00050e5a(iVar3,0);
  FUN_00050e90(iVar3,0);
  FUN_00050f7c(iVar3,0);
  FUN_00050da8(iVar3,1);
  FUN_00050d98(iVar3,0);
  iVar3 = param_1 + 0x2d4;
  FUN_000620f0();
  if (*(char *)(param_1 + 0x28) == '\x01') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 8;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (*(char *)(param_1 + 0x28) == '\x01') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 8;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050f7c(iVar3,iVar4);
  FUN_00050da8(iVar3,1);
  FUN_00050d62(iVar3,0xff);
  FUN_00050d1e(iVar3,*(undefined4 *)(param_1 + 0x36));
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050fe8(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  iVar3 = param_1 + 0x28c;
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ea6(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050edc(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e90(iVar3,iVar4);
  iVar4 = *(int *)(param_1 + 0x2c) + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050da0(iVar3,iVar4);
  FUN_00050d88(iVar3,0x19);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050d6a(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  FUN_00050d98(iVar3,0);
  iVar3 = param_1 + 0x298;
  FUN_000620f0();
  FUN_00050e5a(iVar3,0);
  FUN_00050e90(iVar3,0);
  iVar4 = *(int *)(param_1 + 0x2c) + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050da0(iVar3,iVar4);
  FUN_00050d88(iVar3,0x19);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050d6a(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  FUN_00050d98(iVar3,8);
  FUN_000620f0();
  FUN_00050e5a(param_1 + 0x2a4,0);
  FUN_00050e90(param_1 + 0x2a4,0);
  iVar3 = param_1 + 700;
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ea6(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 8;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 6;
  }
  else {
    iVar4 = 2;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 8;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 6;
    }
    else {
      iVar4 = 2;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050edc(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e90(iVar3,iVar4);
  iVar3 = param_1 + 0x2c8;
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 8;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 6;
  }
  else {
    iVar4 = 2;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 8;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 6;
    }
    else {
      iVar4 = 2;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ea6(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 8;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 6;
  }
  else {
    iVar4 = 2;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 8;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 6;
    }
    else {
      iVar4 = 2;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050edc(iVar3,iVar4);
  FUN_00050fb2(iVar3,0);
  FUN_00050d62(iVar3,0);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050fe8(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  FUN_000620f0();
  FUN_00050ea6(param_1 + 0x2b0,0);
  FUN_00050e90(param_1 + 0x2b0,0);
  FUN_000620f0();
  FUN_00050d62(param_1 + 0x2e0,0x33);
  uVar5 = FUN_0004f04c(0x12);
  FUN_00050d1e(param_1 + 0x2e0,uVar5);
  FUN_000620f0();
  FUN_00050d62(param_1 + 0x2ec,0);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar3 = 8;
  }
  else if (cVar1 == '\x02') {
    iVar3 = 6;
  }
  else {
    iVar3 = 2;
  }
  if (*(int *)(param_1 + 0x2c) * iVar3 + 0x50 < 0x140) {
    iVar3 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar3 = 8;
    }
    else if (cVar1 == '\x02') {
      iVar3 = 6;
    }
    else {
      iVar3 = 2;
    }
    iVar3 = (iVar3 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050edc(param_1 + 0x2ec,iVar3);
  iVar3 = param_1 + 0x238;
  FUN_000620f0();
  iVar4 = *(int *)(param_1 + 0x2c) + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050da0(iVar3,iVar4);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x39));
  FUN_00050d6a(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  FUN_00050d98(iVar3,3);
  iVar3 = param_1 + 0x244;
  FUN_000620f0();
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050d6a(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  iVar4 = *(int *)(param_1 + 0x2c) * 2 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050da0(iVar3,iVar4);
  iVar4 = *(int *)(param_1 + 0x2c) + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050ebc(iVar3,-iVar4);
  FUN_00050d98(iVar3,4);
  FUN_00050ce8(iVar3,400);
  FUN_000620f0();
  if ((*(byte *)(param_1 + 0x24) & 1) == 0) {
    uVar5 = FUN_0004f010(0x12,1);
  }
  else {
    uVar5 = FUN_0004efd0(0x12,2);
  }
  FUN_00050fe8(param_1 + 0x250,uVar5);
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar3 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar3 = 0xc;
  }
  else {
    iVar3 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar3 + 0x50 < 0x140) {
    iVar3 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar3 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar3 = 0xc;
    }
    else {
      iVar3 = 10;
    }
    iVar3 = (iVar3 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e5a(param_1 + 0x25c,iVar3);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar3 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar3 = 0xc;
  }
  else {
    iVar3 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar3 + 0x50 < 0x140) {
    iVar3 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar3 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar3 = 0xc;
    }
    else {
      iVar3 = 10;
    }
    iVar3 = (iVar3 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e90(param_1 + 0x25c,iVar3 / 2);
  iVar3 = param_1 + 0x268;
  FUN_000620f0();
  iVar4 = *(int *)(param_1 + 0x2c) + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050da0(iVar3,iVar4);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x39));
  FUN_00050d6a(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  FUN_00050d1e(iVar3,*(undefined4 *)(param_1 + 0x36));
  FUN_00050d62(iVar3,0x33);
  iVar3 = param_1 + 0x274;
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ea6(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ed4(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 8;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 6;
  }
  else {
    iVar4 = 2;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 8;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 6;
    }
    else {
      iVar4 = 2;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e80(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e90(iVar3,iVar4);
  FUN_000620f0();
  uVar5 = FUN_0004f04c(0x12);
  FUN_00050d1e(param_1 + 0x2f8,uVar5);
  FUN_00050d62(param_1 + 0x2f8,0x7f);
  FUN_000620f0();
  FUN_00050fc2(param_1 + 0x304,0);
  cVar1 = *(char *)(param_1 + 0x28);
  iVar3 = *(int *)(param_1 + 0x2c);
  if (cVar1 == '\x03') {
    if (iVar3 * 8 + 0x50 < 0x140) {
      iVar3 = 1;
    }
    else {
      iVar3 = (iVar3 * 8 + 0x50) / 0xa0;
    }
    iVar3 = iVar3 / 2;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 8;
    }
    if (iVar3 * iVar4 + 0x50 < 0x140) {
      iVar3 = 1;
    }
    else {
      if (cVar1 == '\x01') {
        iVar4 = 0xc;
      }
      else {
        iVar4 = 8;
      }
      iVar3 = (iVar4 * iVar3 + 0x50) / 0xa0;
    }
  }
  FUN_00050f7c(param_1 + 0x304,iVar3);
  iVar3 = param_1 + 0x340;
  FUN_000620f0();
  FUN_00050d6a(iVar3,*(undefined4 *)(param_1 + 0x10));
  iVar4 = *(int *)(param_1 + 0x2c) * 2 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050da0(iVar3,iVar4 << 1);
  FUN_00050d98(iVar3,1);
  iVar4 = *(int *)(param_1 + 0x2c) * 2 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050ed4(iVar3,iVar4 << 1);
  FUN_000620f0();
  iVar3 = *(int *)(param_1 + 0x2c) * 2 + 0x50;
  if (iVar3 < 0x140) {
    iVar3 = 1;
  }
  else {
    iVar3 = iVar3 / 0xa0;
  }
  FUN_00050e24(param_1 + 0x334,-iVar3);
  iVar3 = param_1 + 0x310;
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0x18;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0x14;
  }
  else {
    iVar4 = 0x10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0x18;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0x14;
    }
    else {
      iVar4 = 0x10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050ea6(iVar3,iVar4);
  FUN_00050edc(iVar3,0);
  FUN_00050e90(iVar3,0);
  FUN_00050da8(iVar3,1);
  iVar3 = param_1 + 0x31c;
  FUN_000620f0();
  iVar4 = *(int *)(param_1 + 0x2c) + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050da0(iVar3,iVar4);
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x39));
  FUN_00050d6a(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  FUN_00050d98(iVar3,1);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e5a(iVar3,iVar4);
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar4 = 0xe;
  }
  else if (cVar1 == '\x02') {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar4 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar4 = 0xe;
    }
    else if (cVar1 == '\x02') {
      iVar4 = 0xc;
    }
    else {
      iVar4 = 10;
    }
    iVar4 = (iVar4 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_00050e88(iVar3,iVar4);
  FUN_000620f0();
  cVar1 = *(char *)(param_1 + 0x28);
  if (cVar1 == '\x01') {
    iVar3 = 0x18;
  }
  else if (cVar1 == '\x02') {
    iVar3 = 0x14;
  }
  else {
    iVar3 = 0x10;
  }
  if (*(int *)(param_1 + 0x2c) * iVar3 + 0x50 < 0x140) {
    iVar3 = 1;
  }
  else {
    if (cVar1 == '\x01') {
      iVar3 = 0x18;
    }
    else if (cVar1 == '\x02') {
      iVar3 = 0x14;
    }
    else {
      iVar3 = 0x10;
    }
    iVar3 = (iVar3 * *(int *)(param_1 + 0x2c) + 0x50) / 0xa0;
  }
  FUN_0005101e(param_1 + 0x328,iVar3);
  iVar3 = param_1 + 0x34c;
  FUN_000620f0();
  FUN_00050d62(iVar3,0xff);
  uVar5 = FUN_0004059e();
  FUN_00050d1e(iVar3,uVar5);
  uVar5 = FUN_0004f04c(0x12);
  FUN_00050d3c(iVar3,uVar5);
  FUN_00050f7c(iVar3,0x7fff);
  iVar4 = *(int *)(param_1 + 0x2c) * 0xf + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050fc2(iVar3,iVar4);
  uVar5 = FUN_0004059e();
  FUN_00050f8c(iVar3,uVar5);
  iVar4 = *(int *)(param_1 + 0x2c) * 5 + 0x50;
  if (iVar4 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = iVar4 / 0xa0;
  }
  FUN_00050fba(iVar3,iVar4);
  iVar3 = param_1 + 0x358;
  FUN_000620f0();
  uVar5 = CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33));
  FUN_00050dd0(iVar3,uVar5);
  uVar7 = (undefined1)((uint)uVar5 >> 0x18);
  iVar4 = FUN_0004089c(0);
  if (iVar4 * 2 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = FUN_0004089c(0);
    iVar4 = (iVar4 * 2 + 0x50) / 0xa0;
  }
  FUN_00050dee(iVar3,iVar4);
  FUN_00050cf0(iVar3,CONCAT13(uVar7,*(undefined3 *)(param_1 + 0x33)));
  iVar4 = FUN_0004089c(0);
  if (iVar4 * 2 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = FUN_0004089c(0);
    iVar4 = (iVar4 * 2 + 0x50) / 0xa0;
  }
  FUN_00050d16(iVar3,iVar4);
  iVar4 = FUN_0004089c(0);
  if (iVar4 * 6 + 0x50 < 0x140) {
    iVar4 = 1;
  }
  else {
    iVar4 = FUN_0004089c(0);
    iVar4 = (iVar4 * 6 + 0x50) / 0xa0;
  }
  FUN_00050ef2(iVar3,3,iVar4,uVar2);
  return;
}

