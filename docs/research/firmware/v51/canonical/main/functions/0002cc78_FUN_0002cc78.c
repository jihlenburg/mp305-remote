/* Address: 0002cc78; name: FUN_0002cc78; body bytes: 186 */

void FUN_0002cc78(undefined4 param_1,int *param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int local_50 [5];
  undefined1 local_3c;
  undefined2 local_3b;
  undefined1 local_39;
  undefined4 local_38;
  undefined1 local_34;
  int *local_30;
  uint local_2c;
  undefined1 local_28;
  int local_24;
  int iStack_20;
  int local_1c;
  int iStack_18;
  
  if (param_2 != (int *)0x0) {
    switch((char)param_2[1]) {
    case '\0':
      FUN_00041086(local_50);
      local_28 = *(undefined1 *)((int)param_2 + 0x17);
      local_30 = (int *)CONCAT13(local_30._3_1_,(int3)param_2[5]);
      local_2c = 1;
      FUN_000440c4(param_1,local_50,param_2[3]);
      break;
    case '\x01':
    case '\x02':
    case '\x04':
    case '\b':
      piVar3 = (int *)param_2[2];
      local_24 = *piVar3;
      iStack_20 = piVar3[1];
      local_1c = piVar3[2];
      iStack_18 = piVar3[3];
      uVar1 = FUN_0003db28(&local_24);
      iVar2 = FUN_00041788(uVar1,0xe);
      local_1c = iVar2 + -1 + local_24;
      FUN_0004a57a(local_50,0,0x2c);
      local_3b = (undefined2)param_2[5];
      local_39 = *(undefined1 *)((int)param_2 + 0x16);
      local_3c = *(undefined1 *)((int)param_2 + 0x17);
      local_38 = *(undefined4 *)(*param_2 + 0x10);
      local_30 = &local_24;
      local_2c = (uint)*(ushort *)(*param_2 + 8);
      local_50[0] = param_2[2];
      local_34 = 2;
      FUN_0004337c(param_1,local_50);
    }
  }
  if ((param_3 != 0) && (param_4 != 0)) {
    FUN_00044bbc(param_1,param_3,param_4);
    return;
  }
  return;
}

