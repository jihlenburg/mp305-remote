/* Address: ram:0005db64; name: FUN_ram_0005db64; body bytes: 132 */

int FUN_ram_0005db64(void)

{
  undefined4 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_20000040(0xc0,0x206);
  if (iVar2 != 0) {
    tmos_memset(iVar2,0,0xc0);
    DAT_ram_20001dd8 = iVar2;
    *(undefined1 *)(iVar2 + 10) = 0;
    *(undefined1 *)(iVar2 + 8) = 0;
    uVar1 = DAT_ram_20001eac;
    *(undefined4 *)(iVar2 + 0x74) = DAT_ram_20001ea8;
    *(undefined4 *)(iVar2 + 0x78) = uVar1;
    *(undefined2 *)(iVar2 + 0x30) = 0xffff;
    *(code **)(iVar2 + 0x68) = FUN_ram_0005d9ec;
    *(undefined1 **)(iVar2 + 0x6c) = &LAB_ram_0006013c;
    *(code **)(iVar2 + 0x70) = FUN_ram_0005ffe6;
    FUN_ram_00042570(FUN_ram_00060198,3);
  }
  return iVar2;
}

