/* Address: 0001db74; name: SystemInit; body bytes: 28 */

void SystemInit(void)

{
  DAT_e000ed88 = DAT_e000ed88 | 0xf00000;
  update_system_clock();
  DAT_e000ed08 = 0x10000;
  return;
}

