/* Address: ram:0004e898; name: FUN_ram_0004e898; body bytes: 24 */

undefined4 FUN_ram_0004e898(void)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001a6c != 0) && (*(code **)(DAT_ram_20001a6c + 8) != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0004e8aa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(DAT_ram_20001a6c + 8))();
    return uVar1;
  }
  return 2;
}

