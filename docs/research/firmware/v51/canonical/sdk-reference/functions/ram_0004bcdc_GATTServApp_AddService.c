/* Address: ram:0004bcdc; name: GATTServApp_AddService; body bytes: 52 */

undefined4 GATTServApp_AddService(uint param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001a3c == '\0') && (DAT_ram_20001a3c = '\x01', (param_1 & 1) != 0)) {
    uVar1 = GATTServApp_RegisterService(&DAT_ram_20001954,4,0x10,&DAT_ram_20001994);
    return uVar1;
  }
  return 0;
}

