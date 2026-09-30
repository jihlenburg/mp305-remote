/* Address: 00040b08; name: FUN_00040b08; body bytes: 208 */

void FUN_00040b08(int param_1,int param_2,int param_3,uint param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  if (param_2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = FUN_0004087c(param_1);
  iVar2 = FUN_000408b0(param_1);
  uVar3 = FUN_00040960(param_1);
  if ((iVar2 == 0) || (uVar3 == 0)) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar4 = FUN_000411a4(param_2,uVar1);
  if (iVar4 != param_2) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((param_3 != 0) && (iVar4 = FUN_000411a4(param_3,uVar1), iVar4 != param_3)) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar5 = FUN_00041788(iVar2,uVar1);
  if (param_5 == 0) {
    uVar3 = param_4 / uVar5;
    if (uVar3 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  else if (param_4 <= uVar5 * uVar3 && uVar5 * uVar3 - param_4 != 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_00041554(param_1 + 0x270,iVar2,uVar3,uVar1,uVar5,param_2,param_4);
  iVar4 = param_1 + 0x28c;
  FUN_00041554(iVar4,iVar2,uVar3,uVar1,uVar5,param_3,param_4);
  if (param_3 == 0) {
    iVar4 = 0;
  }
  FUN_00040bc8(param_1,param_1 + 0x270,iVar4);
  if ((param_1 != 0) || (param_1 = DAT_2003a434, DAT_2003a434 != 0)) {
    *(char *)(param_1 + 0x39) = (char)param_5;
  }
  return;
}

