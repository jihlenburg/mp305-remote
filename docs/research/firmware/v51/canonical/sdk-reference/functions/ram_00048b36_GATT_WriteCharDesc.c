/* Address: ram:00048b36; name: GATT_WriteCharDesc; body bytes: 2 */

undefined4 GATT_WriteCharDesc(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  *(undefined2 *)(param_2 + 8) = 0;
  if (*(short *)(param_2 + 8) == 0) {
    uVar1 = FUN_ram_00048602();
    return uVar1;
  }
  return 2;
}

