/* Address: ram:00058388; name: FUN_ram_00058388; body bytes: 146 */

int FUN_ram_00058388(void)

{
  undefined4 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_20000040(0xa0,0x202);
  if (iVar2 != 0) {
    tmos_memset(iVar2,0,0xa0);
    uVar1 = DAT_ram_20001eac;
    DAT_ram_20001de8 = iVar2;
    *(undefined4 *)(iVar2 + 0x94) = DAT_ram_20001ea8;
    *(undefined4 *)(iVar2 + 0x98) = uVar1;
    *(undefined1 *)(iVar2 + 0x40) = 0xff;
    *(undefined1 *)(iVar2 + 6) = 0xb1;
    *(code **)(iVar2 + 0x88) = FUN_ram_0005841a;
    *(undefined1 **)(iVar2 + 0x8c) = &LAB_ram_00058868;
    *(undefined1 *)(iVar2 + 4) = 0;
    *(code **)(iVar2 + 0x90) = FUN_ram_00058710;
    FUN_ram_00042570(FUN_ram_000595ba,4);
  }
  return iVar2;
}

