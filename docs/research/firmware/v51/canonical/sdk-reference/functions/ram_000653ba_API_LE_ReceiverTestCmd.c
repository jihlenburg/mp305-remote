/* Address: ram:000653ba; name: API_LE_ReceiverTestCmd; body bytes: 178 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 API_LE_ReceiverTestCmd(undefined1 *param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 auStack_11 [9];
  
  gp = 0x20004000;
  if (-1 < DAT_ram_20001e8c) {
    DAT_ram_20001e8c = '\x01';
  }
  if (param_2 == 0x201d) {
    DAT_ram_20001d64 = *param_1;
    DAT_ram_20001d98 = 0;
    _DAT_ram_20001d66 = 0x1ff;
    uVar1 = 1;
  }
  else {
    if (param_2 != 0x2033) {
      auStack_11[0] = 0x12;
      goto LAB_ram_00065418;
    }
    DAT_ram_20001d64 = *param_1;
    uVar1 = param_1[1];
    DAT_ram_20001d98 = param_1[2];
    _DAT_ram_20001d66 = CONCAT11(uVar1,0xff);
  }
  DAT_ram_20001d68 = 0;
  auStack_11[0] = FUN_ram_00065a9a(DAT_ram_20001d64,uVar1,DAT_ram_20001d98);
  FUN_ram_00042570(&LAB_ram_000650ea,6);
LAB_ram_00065418:
  thunk_FUN_ram_000521a0(param_2,1,auStack_11);
  return auStack_11[0];
}

