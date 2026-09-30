/* Address: ram:00001000; name: image_entry; body bytes: 4 */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: This function may have set the stack pointer */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void image_entry(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  gp = &DAT_ram_20002000;
  puVar1 = &DAT_ram_00001008;
  puVar2 = &DAT_ram_20002000;
  do {
    *puVar2 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_ram_20002c40);
  puVar1 = &DAT_ram_00009318;
  puVar2 = &DAT_ram_20002c40;
  do {
    *puVar2 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_ram_20002f50);
  puVar1 = &DAT_ram_20002f50;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  } while (puVar1 < &DAT_ram_20006df0);
  _DAT_csreg_0bc0 = 0x1f;
  _DAT_csreg_0804 = 3;
  _mstatus = _mstatus | 0x1888;
  _mtvec = 0x20002003;
  FUN_ram_00007804(FUN_ram_0000780e);
  FUN_ram_00007846();
  mepc = application_main;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

