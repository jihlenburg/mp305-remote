/* Address: ram:00002844; name: FUN_ram_00002844; body bytes: 42 */

uint FUN_ram_00002844(int param_1)

{
  undefined1 *puVar1;
  uint uVar2;
  
  gp = &DAT_ram_20002000;
  uVar2 = 0;
  while (DAT_ram_4000300a != '\0') {
    puVar1 = (undefined1 *)(param_1 + uVar2);
    uVar2 = uVar2 + 1;
    *puVar1 = DAT_ram_40003008;
  }
  return uVar2 & 0xffff;
}

