/* Address: 00014202; name: FUN_00014202; body bytes: 52 */

undefined4 FUN_00014202(int param_1,undefined4 param_2,undefined2 *param_3)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if (param_3 != (undefined2 *)0x0) {
    FUN_0001429c(param_1,param_2,*param_3);
    *(ushort *)(param_1 + 4) = *(ushort *)(param_1 + 4) & 0xfeff | param_3[1] & 0x100;
    FUN_00014236(param_1,param_2,*(undefined1 *)(param_3 + 2));
    uVar1 = 0;
  }
  return uVar1;
}

