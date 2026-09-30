/* Address: ram:00007f4a; name: FUN_ram_00007f4a; body bytes: 70 */

undefined4 * FUN_ram_00007f4a(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  gp = &DAT_ram_20002000;
  iVar1 = (param_2 + -1) * 0x68;
  puVar2 = (undefined4 *)FUN_ram_000082ae(param_1,iVar1 + 0x74);
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = 0;
    puVar2[1] = param_2;
    puVar2[2] = puVar2 + 3;
    FUN_ram_00001d1a(puVar2 + 3,0,iVar1 + 0x68);
  }
  return puVar2;
}

