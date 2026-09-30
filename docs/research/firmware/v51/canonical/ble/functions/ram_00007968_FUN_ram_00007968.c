/* Address: ram:00007968; name: FUN_ram_00007968; body bytes: 68 */

void FUN_ram_00007968(undefined4 param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_ram_20002eb8_ram_20002f48;
  gp = &DAT_ram_20002000;
  if ((PTR_DAT_ram_20002eb8_ram_20002f48 != (undefined *)0x0) &&
     (*(int *)(PTR_DAT_ram_20002eb8_ram_20002f48 + 0x18) == 0)) {
    FUN_ram_00007f90(PTR_DAT_ram_20002eb8_ram_20002f48);
  }
  FUN_ram_00008402(puVar1,*(undefined4 *)(puVar1 + 8),param_1);
  return;
}

