/* Address: ram:0000773c; name: find_saved_host_id; body bytes: 88 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Compares 16 input bytes with stored host IDs. Uses SDK tmos_memcmp boolean semantics. */

undefined4 find_saved_host_id(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 extraout_a3;
  undefined4 uVar3;
  undefined4 extraout_a3_00;
  undefined4 extraout_a4;
  undefined4 uVar4;
  undefined4 extraout_a4_00;
  
  gp = &DAT_ram_20002000;
  uVar1 = 0;
  load_saved_host_ids();
  uVar3 = extraout_a3;
  uVar4 = extraout_a4;
  while( true ) {
    if (DAT_ram_20002fee <= uVar1) {
      return 0;
    }
    iVar2 = (*_DAT_ram_0004003c)
                      (param_1,&DAT_ram_200042b0 + uVar1 * 0x10,0x10,uVar3,uVar4,_DAT_ram_0004003c);
    if (iVar2 != 0) break;
    uVar1 = uVar1 + 1 & 0xff;
    uVar3 = extraout_a3_00;
    uVar4 = extraout_a4_00;
  }
  gp = &DAT_ram_20002000;
  return 1;
}

