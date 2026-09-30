/* Address: ram:00003fac; name: route_main_reply_to_gatt; body bytes: 200 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Routes trailing 0x31 to AF01 with prefix 0x31; otherwise AF02. Saves host after successful bind
   reply notification. */

void route_main_reply_to_gatt(int param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  char local_120;
  undefined1 auStack_11f [267];
  
  gp = &DAT_ram_20002000;
  param_1 = param_1 * 0x218;
  pcVar2 = &DAT_ram_20003b58 + param_1;
  uVar3 = *(ushort *)(&DAT_ram_20003b56 + param_1) & 0xff;
  cVar1 = pcVar2[uVar3 - 1];
  if (cVar1 == '1') {
    FUN_ram_00001d1a(&local_120,0,0x100);
    (*_DAT_ram_0004004c)(auStack_11f,pcVar2,uVar3 - 1);
    local_120 = cVar1;
    notify_af01(&local_120,uVar3);
  }
  else {
    notify_af02(pcVar2,uVar3 - 1 & 0xffff);
  }
  if (*pcVar2 == '\x19') {
    if (DAT_ram_20002f88 == '\0' && (&DAT_ram_20003b59)[param_1] == '\0') {
      save_host_id(&DAT_ram_20005130);
      DAT_ram_20002ff4 = 2;
    }
  }
  return;
}

