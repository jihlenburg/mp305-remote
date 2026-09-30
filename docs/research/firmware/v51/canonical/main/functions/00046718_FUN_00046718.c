/* Address: 00046718; name: FUN_00046718; body bytes: 34 */

undefined4 FUN_00046718(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 8);
  if ((((sVar1 != 0x1a) && (sVar1 != 0x19)) && (sVar1 != 0x1b)) &&
     (((sVar1 != 0x1d && (sVar1 != 0x1c)) && (sVar1 != 0x1e)))) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x10);
}

