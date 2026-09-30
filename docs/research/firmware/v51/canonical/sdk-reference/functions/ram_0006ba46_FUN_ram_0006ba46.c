/* Address: ram:0006ba46; name: FUN_ram_0006ba46; body bytes: 68 */

/* WARNING: This function may have set the stack pointer */

void FUN_ram_0006ba46(void)

{
  undefined4 *puVar1;
  code *pcVar2;
  
  gp = 0x20004000;
  puVar1 = &DAT_ram_00040280;
  pcVar2 = FUN_ram_20000010;
  do {
    *(undefined4 *)pcVar2 = *puVar1;
    puVar1 = puVar1 + 1;
    pcVar2 = pcVar2 + 4;
  } while (pcVar2 < FUN_ram_20000040);
  FUN_ram_0006b9d4();
  return;
}

