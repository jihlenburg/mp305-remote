/* Address: ram:0004da64; name: FUN_ram_0004da64; body bytes: 142 */

int FUN_ram_0004da64(undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined4 param_4,
                    code *param_5)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined2 uStack_28;
  short sStack_26;
  undefined1 *puStack_24;
  
  gp = 0x20004000;
  puVar2 = (undefined1 *)FUN_ram_0004c868(0x17,2);
  if (puVar2 == (undefined1 *)0x0) {
    iVar3 = 0x13;
  }
  else {
    sStack_26 = 0;
    if (param_5 != (code *)0x0) {
      sStack_26 = (*param_5)(puVar2 + 4,param_4);
    }
    *puVar2 = param_2;
    puVar2[1] = param_3;
    puVar2[3] = (char)((ushort)sStack_26 >> 8);
    cVar1 = DAT_ram_20001a62;
    uStack_28 = 5;
    puVar2[2] = (char)sStack_26;
    sStack_26 = sStack_26 + 4;
    puStack_24 = puVar2;
    if (cVar1 == '\0') {
      iVar3 = FUN_ram_0004d412(param_1,&uStack_28);
    }
    else {
      iVar3 = FUN_ram_0004d656();
    }
    if (iVar3 != 0) {
      FUN_ram_20000104(puVar2);
    }
  }
  return iVar3;
}

