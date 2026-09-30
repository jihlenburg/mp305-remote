/* Address: ram:000491bc; name: GATT_bm_free; body bytes: 28 */

void GATT_bm_free(void)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00048726();
  if (iVar1 != 0) {
    FUN_ram_20000104();
    return;
  }
  return;
}

