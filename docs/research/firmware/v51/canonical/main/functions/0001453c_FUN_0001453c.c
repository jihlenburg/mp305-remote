/* Address: 0001453c; name: FUN_0001453c; body bytes: 20 */

undefined4 FUN_0001453c(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = 1 << (param_2 & 0xff) & 0xff;
  if (param_3 == 1) {
    *(uint *)(param_1 + 0x1c) = uVar1;
  }
  else {
    *(uint *)(param_1 + 0x34) = uVar1;
  }
  return 0;
}

