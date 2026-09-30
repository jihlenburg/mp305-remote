/* Address: ram:000484ac; name: GGS_AddService; body bytes: 52 */

undefined4 GGS_AddService(uint param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001a26 == '\0') && (DAT_ram_20001a26 = '\x01', (param_1 & 1) != 0)) {
    uVar1 = GATTServApp_RegisterService(&DAT_ram_200018b8,9,0x10,&PTR_LAB_ram_00047f10_ram_20001948)
    ;
    return uVar1;
  }
  return 0;
}

