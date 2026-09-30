/* Address: ram:0004a6d0; name: FUN_ram_0004a6d0; body bytes: 168 */

int FUN_ram_0004a6d0(undefined4 param_1,undefined4 param_2,undefined2 *param_3,undefined4 param_4,
                    undefined4 param_5,int param_6)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  undefined2 auStack_22 [3];
  
  gp = 0x20004000;
  pcVar2 = (char *)GATT_FindHandle(param_2,auStack_22);
  iVar1 = 1;
  if (pcVar2 != (char *)0x0) {
    iVar1 = 0xe;
    iVar3 = FUN_ram_0004a156(auStack_22[0]);
    if ((((iVar3 != 0) && (*(code **)(iVar3 + 4) != (code *)0x0)) &&
        (iVar1 = (**(code **)(iVar3 + 4))(param_1,pcVar2,param_3,param_4,param_5,param_6),
        iVar1 == 0)) &&
       (((param_6 != 0xfe && (*pcVar2 == '\x02')) && (**(short **)(pcVar2 + 4) == 0x2902)))) {
      FUN_ram_0004a032(param_1,param_2,*param_3);
    }
  }
  return iVar1;
}

