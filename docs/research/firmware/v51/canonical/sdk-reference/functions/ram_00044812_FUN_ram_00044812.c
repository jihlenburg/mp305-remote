/* Address: ram:00044812; name: FUN_ram_00044812; body bytes: 180 */

void FUN_ram_00044812(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined1 uVar4;
  
  gp = 0x20004000;
  puVar2 = (undefined1 *)tmos_msg_allocate(0xc);
  if (puVar2 == (undefined1 *)0x0) {
    return;
  }
  iVar3 = FUN_ram_0004df14(param_2);
  uVar1 = DAT_ram_20001d51;
  uVar4 = DAT_ram_20001c07;
  if ((((iVar3 != 0) && (*(char *)(iVar3 + 0xc) != '\b')) && (uVar4 = uVar1, param_1 == 0)) &&
     (*(code **)(DAT_ram_20001abc + 8) != (code *)0x0)) {
    (**(code **)(DAT_ram_20001abc + 8))(param_2,param_3,param_4,param_5);
  }
  *puVar2 = 0xd0;
  puVar2[1] = (char)param_1;
  puVar2[2] = 7;
  *(short *)(puVar2 + 4) = (short)param_2;
  *(short *)(puVar2 + 6) = (short)param_3;
  *(short *)(puVar2 + 8) = (short)param_4;
  *(short *)(puVar2 + 10) = (short)param_5;
  tmos_msg_send(uVar4,puVar2);
  return;
}

