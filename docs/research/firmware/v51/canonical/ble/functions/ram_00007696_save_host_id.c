/* Address: ram:00007696; name: save_host_id; body bytes: 166 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Appends a 16-byte ID, shifts when five slots are filled, erases and writes offset 0x6f00. */

void save_host_id(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  
  gp = &DAT_ram_20002000;
  load_saved_host_ids();
  uVar2 = (uint)DAT_ram_20002fee;
  if (4 < uVar2) {
    for (uVar1 = 0; uVar2 = DAT_ram_20002fee - 1, (int)uVar1 < (int)uVar2; uVar1 = uVar1 + 1 & 0xff)
    {
      (*_DAT_ram_0004004c)(&DAT_ram_200042b0 + uVar1 * 0x10,&DAT_ram_200042c0 + uVar1 * 0x10,0x10);
    }
  }
  (*_DAT_ram_0004004c)(&DAT_ram_200042b0 + uVar2 * 0x10,param_1,0x10);
  FUN_ram_200028d6(9,0x6f00,0,0x100);
  FUN_ram_200028d6(10,0x6f00,&DAT_ram_200042b0,0x50);
  return;
}

