/* Address: ram:0005d946; name: FUN_ram_0005d946; body bytes: 84 */

void FUN_ram_0005d946(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  gp = 0x20004000;
  puVar1 = DAT_ram_20001e1c;
  while (puVar1 != (undefined1 *)0x0) {
    FUN_ram_00042494(*puVar1);
    puVar2 = *(undefined1 **)(puVar1 + 0x3c);
    *puVar1 = 0xff;
    FUN_ram_20000104(puVar1);
    puVar1 = puVar2;
  }
  DAT_ram_20001e1c = (undefined1 *)0x0;
  DAT_ram_20001e18 = 0;
  return;
}

