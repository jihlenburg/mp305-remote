/* Address: ram:0006561c; name: API_LE_TestEndCmd; body bytes: 90 */

undefined4 API_LE_TestEndCmd(void)

{
  undefined1 uStack_14;
  undefined1 uStack_13;
  undefined1 uStack_12;
  
  gp = 0x20004000;
  DAT_ram_20001e8c = 0;
  if (DAT_ram_20001d66 == -1) {
    uStack_14 = LL_TestEnd(&uStack_13);
  }
  else {
    uStack_14 = LL_TestEnd(0);
    uStack_13 = 0;
    uStack_12 = 0;
  }
  thunk_FUN_ram_000521a0(0x201f,3,&uStack_14);
  tmos_stop_task(DAT_ram_20001b67,0x2000);
  return 0;
}

