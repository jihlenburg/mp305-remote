/* Address: ram:00007e72; name: FUN_ram_00007e72; body bytes: 100 */

undefined4 FUN_ram_00007e72(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  gp = &DAT_ram_20002000;
  if (param_2[4] == 0) {
    return 0;
  }
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) == 0)) {
    FUN_ram_00007f90();
  }
  if (param_2 == &DAT_ram_00009234) {
    param_2 = *(undefined4 **)(param_1 + 4);
  }
  else if (param_2 == (undefined4 *)&DAT_ram_00009254) {
    param_2 = *(undefined4 **)(param_1 + 8);
  }
  else if (param_2 == (undefined4 *)&DAT_ram_00009214) {
    param_2 = *(undefined4 **)(param_1 + 0xc);
  }
  if (*(short *)(param_2 + 3) != 0) {
    uVar1 = FUN_ram_00007d36(param_1);
    return uVar1;
  }
  return 0;
}

