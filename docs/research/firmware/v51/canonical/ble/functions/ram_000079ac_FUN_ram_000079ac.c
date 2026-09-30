/* Address: ram:000079ac; name: FUN_ram_000079ac; body bytes: 46 */

void FUN_ram_000079ac(undefined4 param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_ram_20002eb8_ram_20002f48;
  gp = &DAT_ram_20002000;
  if ((PTR_DAT_ram_20002eb8_ram_20002f48 != (undefined *)0x0) &&
     (*(int *)(PTR_DAT_ram_20002eb8_ram_20002f48 + 0x18) == 0)) {
    FUN_ram_00007f90(PTR_DAT_ram_20002eb8_ram_20002f48,param_1);
  }
  FUN_ram_00008a52(puVar1,param_1,*(undefined4 *)(puVar1 + 8));
  return;
}

