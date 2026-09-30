/* Address: ram:0004cbe6; name: FUN_ram_0004cbe6; body bytes: 252 */

void FUN_ram_0004cbe6(undefined4 param_1,uint param_2,undefined2 *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined2 *puVar4;
  undefined1 *puStack_28;
  ushort uStack_24;
  
  gp = 0x20004000;
  if ((ushort)param_3[1] < 0x80) {
    if (((0x16 < (ushort)param_3[2]) && (0x16 < (ushort)param_3[3])) &&
       ((ushort)param_3[3] <= (ushort)param_3[2])) {
      puStack_28 = (undefined1 *)0x0;
      iVar1 = FUN_ram_0004c3ac(*param_3);
      if (iVar1 == 0) {
        iVar1 = 2;
      }
      else {
        uVar2 = FUN_ram_0004c5a0();
        if ((uVar2 < *(byte *)(iVar1 + 8)) &&
           (iVar3 = FUN_ram_0004c25c(param_1,0xff,iVar1,&puStack_28), iVar3 == 0)) {
          puVar4 = *(undefined2 **)(puStack_28 + 0xc);
          *puVar4 = param_3[4];
          puVar4[1] = param_3[1];
          puVar4[2] = param_3[2];
          puVar4[3] = param_3[3];
          puVar4[4] = *(undefined2 *)(iVar1 + 4);
          if (*(code **)(iVar1 + 0xc) == (code *)0x0) {
            iVar1 = 0;
          }
          else {
            iVar1 = (**(code **)(iVar1 + 0xc))(param_1,param_2 & 0xff,param_3);
            if (iVar1 == 0xffff) {
              *puStack_28 = 6;
              puStack_28[4] = (char)param_2;
              FUN_ram_0004c5ea(puStack_28,0x1e,0xffff);
              gp = 0x20004000;
              return;
            }
          }
        }
        else {
          iVar1 = 4;
        }
      }
      FUN_ram_0004dd24(param_1,param_2,iVar1,puStack_28);
      gp = 0x20004000;
      return;
    }
    puStack_28 = (undefined1 *)((uint)puStack_28 & 0xffff0000);
  }
  else {
    puStack_28 = (undefined1 *)0x2;
    uStack_24 = param_3[1];
  }
  FUN_ram_0004ddcc(param_1,param_2 & 0xff,&puStack_28);
  return;
}

