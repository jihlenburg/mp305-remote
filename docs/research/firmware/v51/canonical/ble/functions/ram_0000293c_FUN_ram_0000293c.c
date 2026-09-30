/* Address: ram:0000293c; name: FUN_ram_0000293c; body bytes: 42 */

uint FUN_ram_0000293c(int param_1)

{
  undefined1 *puVar1;
  uint uVar2;
  
  gp = &DAT_ram_20002000;
  uVar2 = 0;
  while (DAT_ram_4000340a != '\0') {
    puVar1 = (undefined1 *)(param_1 + uVar2);
    uVar2 = uVar2 + 1;
    *puVar1 = DAT_ram_40003408;
  }
  return uVar2 & 0xffff;
}

