��1��FlexRay���� 1������test��ѧϰ��
node1_node2_F1H:����FlexRay����node1��RH850/F1H��,node2��RH850/F1H������д

��2��FlexRay���� 2������ʵ�ʲ��ԣ�
node1_F1H: ����FlexRay����node1��RH850/F1H������д
node2_F1K: ����FlexRay����node2��RH850/F1KH-D8������д

Settings:
[1]Baudrate:
   10Mbps
[2]cluster:
   2 nodes
[3]10 slots in cycle
   9 slots with only static segment
[4]payload Number:
   2bytes,4bytes,127bytes
[5]bus load: about 100%
[6]slot assignment:
for example, 2bytes payload.
node 1 header:
/* FID,CYC,CHA,CHB,CFG,PPIT,TXM,MBI,PL,DP         Tx node */
/*MB_0*/  { 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 36 },    /* Node1 */
/*MB_1*/  { 2 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 37 },    /* Node2 */
/*MB_2*/  { 3 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 38 },    /* Node1 */
/*MB_3*/  { 4 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 39 },    /* Node2 */
/*MB_4*/  { 5 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 40 },    /* Node1 */
/*MB_5*/  { 6 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 41 },    /* Node2 */
/*MB_6*/  { 7 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 1 , 42 },    /* Node1 */
/*MB_7*/  { 8 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 43 },    /* Node2 */
/*MB_8*/  { 9 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 1 , 44 },    /* Node1 */

node 2 header:
/* FID,CYC,CHA,CHB,CFG,PPIT,TXM,MBI,PL,DP         Tx node */
/*MB_0*/  { 2 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 36 },    /* Node2 */
/*MB_1*/  { 1 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 37 },    /* Node1 */
/*MB_2*/  { 3 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 38 },    /* Node1 */
/*MB_3*/  { 4 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 39 },    /* Node2 */
/*MB_4*/  { 5 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 40 },    /* Node1 */
/*MB_5*/  { 6 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 1 , 41 },    /* Node2 */
/*MB_6*/  { 7 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 42 },    /* Node1 */
/*MB_7*/  { 8 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 1 , 43 },    /* Node2 */
/*MB_8*/  { 9 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 44 },    /* Node1 */
[7]test data
0x00,0xff,0xaa,0x55,0x33,0xcc,0x66,0x99
