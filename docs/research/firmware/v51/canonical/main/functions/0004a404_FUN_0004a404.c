/* Address: 0004a404; name: FUN_0004a404; body bytes: 304 */

void FUN_0004a404(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  
  if (param_3 < 0x10) {
    for (; param_3 != 0; param_3 = param_3 - 1) {
      *(undefined1 *)param_1 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      param_1 = (undefined4 *)((int)param_1 + 1);
    }
    return;
  }
  uVar1 = (uint)param_1 & 3;
  if (((uint)param_2 & 3) == uVar1) {
    if (uVar1 != 0) {
      iVar2 = 4 - uVar1;
      for (; (iVar2 != 0 && (param_3 != 0)); param_3 = param_3 - 1) {
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        iVar2 = iVar2 + -1;
        param_2 = (undefined4 *)((int)param_2 + 1);
        param_1 = (undefined4 *)((int)param_1 + 1);
      }
    }
    for (; 0x20 < param_3; param_3 = param_3 - 0x20) {
      *param_1 = *param_2;
      param_1[1] = param_2[1];
      param_1[2] = param_2[2];
      param_1[3] = param_2[3];
      param_1[4] = param_2[4];
      param_1[5] = param_2[5];
      param_1[6] = param_2[6];
      param_1[7] = param_2[7];
      param_2 = param_2 + 8;
      param_1 = param_1 + 8;
    }
    for (; param_3 != 0; param_3 = param_3 - 1) {
      *(undefined1 *)param_1 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      param_1 = (undefined4 *)((int)param_1 + 1);
    }
    return;
  }
  for (; 0x20 < param_3; param_3 = param_3 - 0x20) {
    *(undefined1 *)param_1 = *(undefined1 *)param_2;
    *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
    *(undefined1 *)((int)param_1 + 3) = *(undefined1 *)((int)param_2 + 3);
    *(undefined1 *)(param_1 + 1) = *(undefined1 *)(param_2 + 1);
    *(undefined1 *)((int)param_1 + 5) = *(undefined1 *)((int)param_2 + 5);
    *(undefined1 *)((int)param_1 + 6) = *(undefined1 *)((int)param_2 + 6);
    *(undefined1 *)((int)param_1 + 7) = *(undefined1 *)((int)param_2 + 7);
    *(undefined1 *)(param_1 + 2) = *(undefined1 *)(param_2 + 2);
    *(undefined1 *)((int)param_1 + 9) = *(undefined1 *)((int)param_2 + 9);
    *(undefined1 *)((int)param_1 + 10) = *(undefined1 *)((int)param_2 + 10);
    *(undefined1 *)((int)param_1 + 0xb) = *(undefined1 *)((int)param_2 + 0xb);
    *(undefined1 *)(param_1 + 3) = *(undefined1 *)(param_2 + 3);
    *(undefined1 *)((int)param_1 + 0xd) = *(undefined1 *)((int)param_2 + 0xd);
    *(undefined1 *)((int)param_1 + 0xe) = *(undefined1 *)((int)param_2 + 0xe);
    *(undefined1 *)((int)param_1 + 0xf) = *(undefined1 *)((int)param_2 + 0xf);
    *(undefined1 *)(param_1 + 4) = *(undefined1 *)(param_2 + 4);
    *(undefined1 *)((int)param_1 + 0x11) = *(undefined1 *)((int)param_2 + 0x11);
    *(undefined1 *)((int)param_1 + 0x12) = *(undefined1 *)((int)param_2 + 0x12);
    *(undefined1 *)((int)param_1 + 0x13) = *(undefined1 *)((int)param_2 + 0x13);
    *(undefined1 *)(param_1 + 5) = *(undefined1 *)(param_2 + 5);
    *(undefined1 *)((int)param_1 + 0x15) = *(undefined1 *)((int)param_2 + 0x15);
    *(undefined1 *)((int)param_1 + 0x16) = *(undefined1 *)((int)param_2 + 0x16);
    *(undefined1 *)((int)param_1 + 0x17) = *(undefined1 *)((int)param_2 + 0x17);
    *(undefined1 *)(param_1 + 6) = *(undefined1 *)(param_2 + 6);
    *(undefined1 *)((int)param_1 + 0x19) = *(undefined1 *)((int)param_2 + 0x19);
    *(undefined1 *)((int)param_1 + 0x1a) = *(undefined1 *)((int)param_2 + 0x1a);
    *(undefined1 *)((int)param_1 + 0x1b) = *(undefined1 *)((int)param_2 + 0x1b);
    *(undefined1 *)(param_1 + 7) = *(undefined1 *)(param_2 + 7);
    *(undefined1 *)((int)param_1 + 0x1d) = *(undefined1 *)((int)param_2 + 0x1d);
    *(undefined1 *)((int)param_1 + 0x1e) = *(undefined1 *)((int)param_2 + 0x1e);
    *(undefined1 *)((int)param_1 + 0x1f) = *(undefined1 *)((int)param_2 + 0x1f);
    param_2 = param_2 + 8;
    param_1 = param_1 + 8;
  }
  for (; param_3 != 0; param_3 = param_3 - 1) {
    *(undefined1 *)param_1 = *(undefined1 *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  return;
}

