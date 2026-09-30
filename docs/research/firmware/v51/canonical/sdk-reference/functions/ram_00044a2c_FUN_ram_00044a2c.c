/* Address: ram:00044a2c; name: FUN_ram_00044a2c; body bytes: 154 */

void FUN_ram_00044a2c(undefined1 param_1)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001c07 != -1) &&
     (puVar1 = (undefined1 *)tmos_msg_allocate(10), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 0xd0;
    puVar1[1] = param_1;
    puVar1[2] = 8;
    puVar1[3] = DAT_ram_20001c06;
    tmos_memcpy(puVar1 + 4,&DAT_ram_200019d8,6);
    tmos_msg_send(DAT_ram_20001c07,puVar1);
  }
  if (((DAT_ram_20001c06 == '\x03') && (DAT_ram_200019f0 != 0)) &&
     (*(code **)(DAT_ram_200019f0 + 8) != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x00044ab8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(DAT_ram_200019f0 + 8))();
    return;
  }
  return;
}

