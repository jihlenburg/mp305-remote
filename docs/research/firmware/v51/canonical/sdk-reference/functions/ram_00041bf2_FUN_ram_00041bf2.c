/* Address: ram:00041bf2; name: FUN_ram_00041bf2; body bytes: 56 */

uint * FUN_ram_00041bf2(uint *param_1,int param_2)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  
  gp = 0x20004000;
  puVar1 = (uint *)((int)param_1 - param_2);
  puVar3 = DAT_ram_20001b5c;
  do {
    if (DAT_ram_20001b54 == puVar3) {
      gp = 0x20004000;
      return param_1;
    }
    puVar2 = puVar3 + 2;
    puVar3 = (uint *)*puVar3;
  } while ((((param_1 < puVar2) || (puVar3 <= param_1)) || (puVar1 < puVar2)) || (puVar3 <= puVar1))
  ;
  return puVar1;
}

