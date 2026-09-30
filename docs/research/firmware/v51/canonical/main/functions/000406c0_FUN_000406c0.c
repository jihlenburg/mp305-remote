/* Address: 000406c0; name: FUN_000406c0; body bytes: 382 */

int * FUN_000406c0(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int *piVar6;
  
  piVar2 = (int *)FUN_0004a162(&DAT_2003a424);
  if (piVar2 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_0004a5da(piVar2,0x310);
  *piVar2 = param_1;
  piVar2[1] = param_2;
  piVar2[2] = -1;
  piVar2[3] = -1;
  piVar2[4] = 0;
  piVar2[5] = 0;
  piVar2[0xe] = piVar2[0xe] | 0x10000;
  piVar2[6] = 0x82;
  *(undefined1 *)((int)piVar2 + 0x3b) = 0x12;
  iVar3 = FUN_0004a360(0x4c);
  piVar2[0xaa] = iVar3;
  if (iVar3 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((code *)piVar2[0xab] != (code *)0x0) {
    (*(code *)piVar2[0xab])(piVar2);
  }
  *(undefined4 *)(piVar2[0xaa] + 4) = 0;
  *(undefined4 *)(piVar2[0xaa] + 8) = 0;
  *(int *)(piVar2[0xaa] + 0xc) = param_1 + -1;
  *(int *)(piVar2[0xaa] + 0x10) = param_2 + -1;
  *(undefined1 *)(piVar2[0xaa] + 0x14) = *(undefined1 *)((int)piVar2 + 0x3b);
  piVar2[0x98] = 1;
  iVar3 = FUN_00052708();
  piVar2[0xbf] = iVar3;
  FUN_0004a152(piVar2 + 0x99,0x10);
  piVar1 = DAT_2003a434;
  DAT_2003a434 = piVar2;
  iVar3 = FUN_0005285c(0x409b5,10,piVar2);
  piVar2[0xbe] = iVar3;
  if (iVar3 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar3 = FUN_000526b0();
  if (iVar3 == 0) {
    uVar4 = FUN_0004f04c(0);
    uVar5 = FUN_0004f04c(5);
    iVar3 = FUN_000525b8(piVar2,uVar5,uVar4,0,&DAT_0006a6dc);
  }
  else {
    iVar3 = FUN_000525a0();
  }
  piVar2[0xbd] = iVar3;
  iVar3 = FUN_0004b384(0);
  piVar2[0xb1] = iVar3;
  piVar6 = piVar2 + 0xae;
  iVar3 = FUN_0004b384(0);
  piVar2[0xb0] = iVar3;
  iVar3 = FUN_0004b384(0);
  piVar2[0xaf] = iVar3;
  iVar3 = FUN_0004b384(0);
  *piVar6 = iVar3;
  FUN_0004e210(piVar2[0xb1]);
  FUN_0004e210(piVar2[0xaf]);
  FUN_0004e210(*piVar6);
  FUN_0004e00e(piVar2[0xaf],2);
  FUN_0004e00e(*piVar6,2);
  FUN_0004e822(piVar2[0xb1],0);
  FUN_0004e822(piVar2[0xaf],0);
  FUN_0004e822(*piVar6,0);
  FUN_0004d3d8(piVar2[0xb0]);
  DAT_2003a434 = piVar2;
  if (piVar1 != (int *)0x0) {
    DAT_2003a434 = piVar1;
  }
  FUN_000406b2(piVar2,0x28041,0x35,0);
  FUN_00052a82(piVar2[0xbe]);
  return piVar2;
}

