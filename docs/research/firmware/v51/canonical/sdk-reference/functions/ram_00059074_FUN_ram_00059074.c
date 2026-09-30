/* Address: ram:00059074; name: FUN_ram_00059074; body bytes: 68 */

undefined4 FUN_ram_00059074(int param_1)

{
  uint *puVar1;
  
  gp = 0x20004000;
  FUN_ram_00058a3a();
  *(undefined4 *)(DAT_ram_20001eb0 + 0x70) = *(undefined4 *)(param_1 + 0x94);
  puVar1 = DAT_ram_20001e88;
  *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
  puVar1[0xb] = puVar1[0xb] & 0xfffffffc;
  FUN_ram_200010ec();
  return 0;
}

