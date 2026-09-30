/* Address: ram:0004a296; name: FUN_ram_0004a296; body bytes: 24 */

undefined2 FUN_ram_0004a296(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  
  gp = 0x20004000;
  puVar2 = (undefined2 *)FUN_ram_0004a274();
  if (puVar2 == (undefined2 *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *puVar2;
  }
  return uVar1;
}

