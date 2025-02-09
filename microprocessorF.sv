module registerCluster(input logic [2:0] regEnable,movEnable,input logic [7:0] regIN,input logic clk,output logic [4:0][7:0] databus_ALU,output logic [7:0] databus_REGmove);

logic [4:0][7:0] regM;
logic nothing;

always_ff@(posedge clk)
begin

case(regEnable)
	3'b001: regM[0] <= regIN;
	3'b010: regM[1] <= regIN;
	3'b011: regM[2] <= regIN;
	3'b100: regM[3] <= regIN;
	3'b101: regM[4] <= regIN;
	default: nothing <= 0;
endcase
	
case(movEnable)
	3'b001: databus_REGmove <= regM[0];
	3'b010: databus_REGmove <= regM[1];
	3'b011: databus_REGmove <= regM[2];
	3'b100: databus_REGmove <= regM[3];
	3'b101: databus_REGmove <= regM[4];
	default: nothing <= 0;
	endcase
	databus_ALU <= regM;
end


endmodule



module ADRmodeMemoryJunction(input logic [1:0] ADRMODE,input logic clk,input logic [7:0] memoryToReg,RegToReg,ALU_to_REG,output logic [7:0] content_OUT); //depending on the addressing mode, the data is selected to go into the register cluster. 


always_ff@(negedge clk) 
begin
	case(ADRMODE)
	2'b01:
		begin
		content_OUT <= memoryToReg;
		end
	2'b10:
		begin
		content_OUT <= RegToReg;
		end
	2'b11:	
		begin
	        content_OUT <= ALU_to_REG;
		end
	default:
		begin
		content_OUT <= 0;
		end
	endcase
	
	

end

endmodule

module registerUnit(input logic clk,input logic [1:0] ADRMODE,input logic [2:0] regWriteTo,movEnable, input logic [7:0] ALU_to_REG,input logic [7:0] memoryToReg,output logic [4:0][7:0] databus_ALU);
logic [7:0] selectedMemoryLane;
logic [7:0] databus_REGmove;

ADRmodeMemoryJunction memoryJunction(ADRMODE, clk  ,memoryToReg,databus_REGmove,ALU_to_REG,   selectedMemoryLane);
registerCluster registerCollection( regWriteTo,movEnable,selectedMemoryLane,clk,  databus_ALU,databus_REGmove);

endmodule


module memoryUnit(input logic clk,input logic [2:0] memorySelect,output logic [7:0] MEM_OUT);  //Read only memory. 

always_ff@(posedge clk) 
	begin
	case(memorySelect)

		3'b000: MEM_OUT <= 0;
		3'b001: MEM_OUT <= 1;
		3'b010: MEM_OUT <= 2;
		3'b011: MEM_OUT <= 3;
		3'b100: MEM_OUT <= 4;
		3'b101: MEM_OUT <= 5;
		3'b110: MEM_OUT <= 6;
		3'b111: MEM_OUT <= 7;
		default: MEM_OUT <= 0;
		endcase
	end

endmodule


module MemoryComplex(input logic clk,input logic [1:0] ADRMODE,input logic [2:0] memorySelect,MoveTo,movFrom, input logic [7:0] ALU_to_REG,output logic [4:0][7:0] databus_ALU); //memory stuff

logic [7:0] MEM_OUT;
logic [7:0] memoryToReg;

memoryUnit ReadOnlyMemory(clk,memorySelect,memoryToReg);
registerUnit registerModule(clk,ADRMODE,MoveTo,movFrom,ALU_to_REG,memoryToReg,databus_ALU);

endmodule

module registerController(input logic clk,input logic [1:0] ADRMODE,input logic [2:0] OPCODE,memorySelect,MoveTo,movFrom,output logic [2:0] memorySelectOUT,MoveToOUT,movFromOUT,output logic [1:0] ADRMODE_OUT);
int delay;
always_comb
	begin
	if (OPCODE == 3'b001) //If mov is used, then there are different addressing modes and also register moving/data moving control. 
		begin
		memorySelectOUT = memorySelect;
		ADRMODE_OUT = ADRMODE;
		movFromOUT = movFrom;
		MoveToOUT = MoveTo;
		end
	else if (OPCODE == 3'b010 | OPCODE == 3'b011 | OPCODE == 3'b100 | OPCODE == 3'b101)
		begin
		memorySelectOUT = 0;
		MoveToOUT = memorySelect; //MemorySelect used as destination operand. 
		movFromOUT = 0;
		ADRMODE_OUT = 2'b11;  //ALU_to_reg mode.
		end
	else
		begin
		memorySelectOUT = 0;
		ADRMODE_OUT = 0;
		movFromOUT = 0;
		MoveToOUT = 0;
		end
	end
endmodule

module operandSelector(input logic clk,input wire [4:0][7:0] databus_ALU,input logic [2:0] OPSELECT0,OPSELECT1,output logic [1:0][7:0] arithmeticOP); //Selects which registers to add/subtract or compare. 

logic nothing;

always@(clk)
	begin
	case(OPSELECT0)
		3'b001: arithmeticOP[0] <= databus_ALU[0];
		3'b010: arithmeticOP[0] <= databus_ALU[1];
		3'b011: arithmeticOP[0] <= databus_ALU[2];
		3'b100: arithmeticOP[0] <= databus_ALU[3];
		3'b101: arithmeticOP[0] <= databus_ALU[4];
		default arithmeticOP <= 0;
	endcase

	case(OPSELECT1)
		3'b001: arithmeticOP[1] <= databus_ALU[0];
		3'b010: arithmeticOP[1] <= databus_ALU[1];
		3'b011: arithmeticOP[1] <= databus_ALU[2];
		3'b100: arithmeticOP[1] <= databus_ALU[3];
		3'b101: arithmeticOP[1] <= databus_ALU[4];
		default arithmeticOP <= 0;
	endcase
	end

endmodule

module ALU(input logic [2:0] OPCODE,input logic clk,input wire [1:0][7:0] ArithmeticOP, output logic [7:0] ALU_to_REG); //Does arithmetic, but also sends data back to target register with help of a different module
always_ff@(posedge clk)
	begin
	case(OPCODE)
		3'b010: //ADD
			begin
			ALU_to_REG <= ArithmeticOP[0] + ArithmeticOP[1];
			end
		3'b011: 
			begin
			//SUB
			ALU_to_REG <= ArithmeticOP[0] - ArithmeticOP[1];
			end
		3'b100: 
			begin
			//BT_OR
			ALU_to_REG <= ArithmeticOP[0] | ArithmeticOP[1];
			end
		3'b101: 
			begin
			//BT_AND
			ALU_to_REG <= ArithmeticOP[0] & ArithmeticOP[1];
			end
		default: ALU_to_REG <= 0;
	endcase

	end

endmodule


module cmpHandler(input logic [2:0] OPCODE,input logic [7:0] REG_A, REG_B, output logic [2:0] status); //Compares different situations and returns a status / updates if triggered. 

always_comb
begin	
	status = 0;
if (OPCODE == 3'b110)
begin


	if (REG_A == REG_B)
	begin
		status[0] = 1;
	end
	
	else
	begin
		status[0] = 0;
	end	

	if (REG_A >= REG_B)
	begin
		status[1] = 1;
	end
	
	else	
	begin
		status[1] = 0;
	end

	if (REG_A > REG_B)
	begin
		status[2] = 1;
	end
	else	
	begin
		status[2] = 0;
	end

end
end


endmodule

module statusRegister(input logic [2:0] statusFlag,input logic clk,input logic [2:0] OPCODE,output logic [2:0] statusStore);

always_ff@(posedge clk)
begin
if (OPCODE == 3'b110)
	begin
	statusStore <= statusFlag;
	end
end 


endmodule

module controlUNIT(input logic [31:0] instructionInput,input wire [4:0][7:0] databus_ALU,input logic clk,output logic [2:0] memorySelectOUT,MoveToOUT,movFromOUT,output logic [1:0] ADRMODE_OUT,output logic [1:0][7:0] arithmeticOP_OUT,output logic [2:0] OPCODE);

logic [1:0][7:0] arithmeticOP;
assign arithmeticOP_OUT = arithmeticOP;
assign OPCODE = instructionInput[31:29];


registerController regManager(clk,instructionInput[28:27],instructionInput[31:29],instructionInput[26:24],instructionInput[23:21],instructionInput[20:18],memorySelectOUT,MoveToOUT,movFromOUT,ADRMODE_OUT);
operandSelector opSelect(clk,databus_ALU,instructionInput[23:21],instructionInput[20:18],arithmeticOP);

endmodule



module instructionPUSHER(input logic clk,input logic [2:0] status,output logic [31:0] instruction);
int instructionPointer;
logic [31:0] instructionInternal;
int cycles;
always_comb
begin
	case(instructionPointer)
   
	1: instructionInternal = 32'b001_01_111_001_000_000000000000000000; // MOV 3b111,A
	2: instructionInternal = 32'b001_10_000_010_001_000000000000000000; // MOV B,A
	3: instructionInternal = 32'b001_10_000_011_010_000000000000000000; // MOV C,B
	4: instructionInternal = 32'b001_01_001_100_000_000000000000000000; // MOV 3b001,D
	5: instructionInternal = 32'b001_10_000_101_100_000000000000000000; // MOV E,D
	
	
	default: instructionInternal = 0;
	endcase
end
always_ff@(posedge clk)
begin
cycles <= cycles + 1;
instruction <= instructionInternal;
if (instruction[31:29] == 3'b001 && cycles == 6 )
	begin
	cycles <= 0;
	instructionPointer <= instructionPointer + 1;
	end
else if (instruction[31:29] == 3'b010 && cycles == 2)
	begin
	cycles <= 0;
	instructionPointer <= instructionPointer + 1;	
	end
else if (instruction[31:29] == 3'b011 && cycles == 2)
	begin
	cycles <= 0;
	instructionPointer <= instructionPointer + 1;	
	end
else if (instruction[31:29] == 3'b100 && cycles == 2)
	begin
	cycles <= 0;
	instructionPointer <= instructionPointer + 1;	
	end
else if (instruction[31:29] == 3'b101 && cycles == 2)
	begin
	cycles <= 0;
	instructionPointer <= instructionPointer + 1;	
	end
else if (instruction[31:29] == 3'b110 && cycles == 3)
	begin
	cycles <= 0;
	instructionPointer <= instructionPointer + 1;	
	end 
else if (instruction[31:29] == 3'b000 && cycles == 1)
	begin
	cycles <= 0;
	instructionPointer <= instructionPointer + 1;	
	end

else if (instruction[31:29] == 3'b111 && cycles >= 3)
	begin
	cycles <= 0;
	case(instruction[28:26])	
	3'b001:
		begin
		if (status[0] == 1)
			begin
			instructionPointer <= instructionInternal[25:0];
			end
		else
			begin
			instructionPointer <= instructionPointer + 1;
			end		
		end

	3'b010:

		begin
			if (status[1] == 1)
			begin
			instructionPointer <= instructionInternal[25:0];
			end
		else
			begin
			instructionPointer <= instructionPointer + 1;
			end		
		end
	
	3'b100:
		begin
			if (status[2] == 1)
			begin
			instructionPointer <= instructionInternal[25:0];
			end
		else
			begin
			instructionPointer <= instructionPointer + 1;
			end		
		end

	default:  instructionPointer <= instructionInternal[25:0];
	endcase

	end

	else
		begin

		end

end
endmodule



module microprocessorF(input logic clk,output logic [3:0] REGdisplay0,REGdisplay1,REGdisplay2,REGdisplay3,REGdisplay4, output logic  [2:0] OPCODEDISPLAY);

logic [4:0][7:0] databus_ALU;
logic [2:0] memorySelectOUT,MoveToOUT,movFromOUT;
logic [7:0] ALU_to_REG;
logic [1:0] ADRMODE;
logic [1:0][7:0] registerSelectOPERANDS;
logic [2:0] statusCable;
logic [31:0] instructionInput;
logic [2:0] statusReg;
logic [2:0] ALUCONTROL;

assign REGdisplay0 = databus_ALU[0][3:0];
assign REGdisplay1 = databus_ALU[1][3:0];
assign REGdisplay2 = databus_ALU[2][3:0];
assign REGdisplay3 = databus_ALU[3][3:0];
assign REGdisplay4 = databus_ALU[4][3:0];

instructionPUSHER mainProgram(clk,statusReg,instructionInput);
cmpHandler cmpFlagProvider(instructionInput[31:29],registerSelectOPERANDS[0],registerSelectOPERANDS[1],statusCable);
statusRegister statusFlagREG(statusCable,clk,instructionInput[31:29],statusReg);

controlUNIT mcontrolunit(instructionInput,databus_ALU,clk,memorySelectOUT,MoveToOUT,movFromOUT,ADRMODE,registerSelectOPERANDS,ALUCONTROL);
ALU ALU_UNIT(ALUCONTROL,clk,registerSelectOPERANDS,ALU_to_REG);
MemoryComplex memoryManegmentUnit(clk,ADRMODE,memorySelectOUT,MoveToOUT,movFromOUT,ALU_to_REG,databus_ALU);



assign OPCODEDISPLAY = instructionInput[31:29];

endmodule
