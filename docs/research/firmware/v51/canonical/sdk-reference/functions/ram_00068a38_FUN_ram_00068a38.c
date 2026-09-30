/* Address: ram:00068a38; name: FUN_ram_00068a38; body bytes: 36 */

void FUN_ram_00068a38(ushort *param_1)

{
  ushort *puVar1;
  ushort *puVar2;
  
  gp = 0x20004000;
  puVar1 = param_1;
  do {
    puVar2 = puVar1 + 2;
    *puVar1 = ~*puVar1;
    *(byte *)(puVar1 + 1) = ~(byte)puVar1[1];
    puVar1 = puVar2;
  } while (puVar2 != param_1 + 0xc);
  return;
}

