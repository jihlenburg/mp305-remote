/* Address: ram:00063586; name: RF_FrequencyHoppingShut; body bytes: 120 */

void RF_FrequencyHoppingShut(void)

{
  undefined4 uVar1;
  undefined4 extraout_a3;
  
  gp = 0x20004000;
  RF_Shut();
  DAT_ram_20001eb5 = DAT_ram_20001ee3;
  DAT_ram_20001ebc = DAT_ram_20001ee8;
  tmos_stop_task(DAT_ram_20001ee4,8);
  tmos_stop_task(DAT_ram_20001ee4,4);
  if ((DAT_ram_20001ee0 & 2) == 0) {
    if ((DAT_ram_20001ee0 & 4) == 0) {
      gp = 0x20004000;
      DAT_ram_20001ee0 = 0;
      return;
    }
    uVar1 = 0x24;
  }
  else {
    uVar1 = 0x22;
  }
  (*DAT_ram_20001ec4)(uVar1,0,0,extraout_a3,DAT_ram_20001ee0 & 2,DAT_ram_20001ec4);
  DAT_ram_20001ee0 = 0;
  return;
}

