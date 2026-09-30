/* Address: ram:000624dc; name: BLE_PAControlInit; body bytes: 32 */

void BLE_PAControlInit(int param_1)

{
  gp = 0x20004000;
  DAT_ram_20001e90 = param_1;
  if (param_1 != 0) {
    **(uint **)(param_1 + 4) = **(uint **)(param_1 + 4) | *(uint *)(param_1 + 0x14);
    **(uint **)(param_1 + 0x10) = **(uint **)(param_1 + 0x10) | *(uint *)(param_1 + 8);
  }
  return;
}

