/* Address: 00012222; name: FUN_00012222; body bytes: 26 */

undefined4 FUN_00012222(int param_1,ushort *param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if (param_2 != (ushort *)0x0) {
    *(ushort *)(param_1 + 2) = *param_2 | param_2[1] | param_2[2];
    uVar1 = 0;
  }
  return uVar1;
}

