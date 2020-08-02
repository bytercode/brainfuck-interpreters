function main(argc, argv)
	if (argc == 1) then
		print("Arguments:\nbrainfucker file [path to file]");
		print("brainfucker string [brainfuck code]");
		print("(WARNING! EVERYTHING IS CASE SENSITIVE.)");
		return 0;
	end
	
	if (argc < 3) then
		print("The syntax of the command is incorrect");
		return -1;
	end
	
	local op = argv[1];
	local bfcode = "";
	
	if (op == "string") then
		for i = 2, argc-1, 1 do
			bfcode = bfcode .. argv[i];
		end
	elseif (op == "file") then
		local fl = io.open(argv[2], "r");
		if (fl == nil) then
			print("Error while opening file.");
			return -1;
		end
		io.close(fl);
		local lns = io.lines(argv[2]);
		local fotable = {};
		for i in lns do
			table.insert(fotable, i);
		end
		bfcode = table.concat(fotable, "");
	else
		print("Cannot find command "..op);
		return -1;
	end
	
	local cellssize = 100;
	local cells = {};
	local loopstack = {};
	local ceindex = 0;
	local loopcounter = 0;
	for i = 0, 100, 1 do
		cells[i] = 0;
	end
	
	local i = 1;
	local ssize = string.len(bfcode);
	while (i <= ssize) do
		local cindex = string.sub(bfcode, i, i);
		if (cindex == '.') then
			print(utf8.char(cells[ceindex]));
		elseif (cindex == '+') then
			cells[ceindex] = cells[ceindex] + 1;
			if (cells[ceindex] > 255) then cells[ceindex] = 0; end
		elseif (cindex == '-') then
			cells[ceindex] = cells[ceindex] - 1;
			if (cells[ceindex] < 0) then cells[ceindex] = 255; end
		elseif (cindex == '>') then
			ceindex = ceindex + 1;
			if (ceindex > cellssize-1) then ceindex = 0; end
		elseif (cindex == '<') then
			ceindex = ceindex - 1;
			if (ceindex < 0) then ceindex = cellssize-1; end
		elseif (cindex == '[') then
			if (not(cells[ceindex] == 0)) then
				loopstack[#loopstack + 1] = i;
			else
				local brackcounter = 0;
				while (i <= ssize) do
					i = i + 1;
					local ceindex = string.sub(bfcode, i, i);
					if (ceindex == '[') then
						brackcounter = brackcounter + 1;
					elseif (ceindex == ']') then
						if (brackcounter > 0) then brackcounter = brackcounter - 1;
						else break; end
					end
				end
			end
		elseif (cindex == ']') then
			if (not(cells[ceindex] == 0)) then
				if (#loopstack > 0) then
					i = loopstack[#loopstack];
				end
			else
				loopstack[#loopstack] = nil;
			end
		end
		i = i + 1;
	end
end

main(#arg+1, arg);