import re
import sys
import os

def get_opposite_side(filename):
    base = os.path.basename(filename)
    base = base.lower()
    
    if 'blue' in base:
        color = 'blue'
        opposite_color = 'red'
    else:
        color = 'red'
        opposite_color = 'blue'
        
    if 'left' in base:
        position = 'left'
        opposite_position = 'right'
    else:
        position = 'right'
        opposite_position = 'left'
    
    return opposite_color, opposite_position

def get_output_filename(input_file):
    dir_path = os.path.dirname(input_file)
    opposite_color, opposite_position = get_opposite_side(input_file)
    new_filename = f"{opposite_color}_{opposite_position}_temp.cpp"
    return os.path.join(dir_path, new_filename)

def get_class_name(input_file):
    # Determine color and position from filename
    base = os.path.basename(input_file).lower()
    if 'blue' in base:
        current_color = 'Blue'
        opposite_color = 'Red'
    else:
        current_color = 'Red'
        opposite_color = 'Blue'

    if 'left' in base:
        current_position = 'left'
        opposite_position = 'right'
    else:
        current_position = 'right'
        opposite_position = 'left'

    return current_color, opposite_color, current_position, opposite_position

def mirror_coordinates(cpp_content, input_file):
    # Get color and position information
    current_color, opposite_color, current_position, opposite_position = get_class_name(input_file)
    
    # Replace class definition
    function_pattern = rf'void\s+{current_color}::{current_position}\(\)'
    replacement = f'void {opposite_color}::{opposite_position}()'
    cpp_content = re.sub(function_pattern, replacement, cpp_content, flags=re.IGNORECASE)

    def format_number(num):
        # If number is effectively an integer, return it as integer
        if abs(num - round(num)) < 1e-10:
            return str(round(num))
        # Otherwise return with one decimal place
        return f"{num:.1f}"

    def mirror_angle(angle_val):
        # Convert angle to opposite angle in 360° system
        new_angle = (360 - float(angle_val)) % 360
        if new_angle > 180:
            new_angle -= 360
        return format_number(new_angle)

    def mirror_setpose(match):
        x, y, angle = match.groups()
        x_val = float(x)
        # Flip signs for coordinates
        mirrored_x = format_number(-x_val) if x_val != 0 else "0"
        # Mirror angle
        new_angle = mirror_angle(angle)
        return f'setPose({mirrored_x}, {y}, {new_angle})'

    def mirror_point(match):
        command, x, y, rest = match.groups()
        x_val = float(x)
        mirrored_x = format_number(-x_val) if x_val != 0 else "0"
        return f'{command}Point({mirrored_x}, {y}{rest}'

    def mirror_swing_point(match):
        x, y, drive_side, rest = match.groups()
        x_val = float(x)
        mirrored_x = format_number(-x_val) if x_val != 0 else "0"
        opposite_side = 'LEFT' if drive_side == 'RIGHT' else 'RIGHT'
        return f'swingToPoint({mirrored_x}, {y}, DriveSide::{opposite_side}{rest}'

    def mirror_pose(match):
        x, y, angle, time, options, last = match.groups()
        x_val = float(x)
        mirrored_x = format_number(-x_val) if x_val != 0 else "0"
        new_angle = mirror_angle(angle)
        return f'moveToPose({mirrored_x}, {y}, {new_angle}, {time}, {options}, {last})'

    def ensure_assets(content):
        extern_match = re.search(r'extern bool off;\s*', content)
        if not extern_match:
            return content
            
        insert_position = extern_match.end()
        content = re.sub(r'ASSET\([^)]+\);\s*', '', content)
        
        if 'blue' in input_file.lower():
            assets = "\nASSET(bl1_v2_txt);\nASSET(rr1_v2_txt);\n"
        else:
            assets = "\nASSET(rr1_v2_txt);\nASSET(bl1_v2_txt);\n"
            
        return content[:insert_position] + assets + content[insert_position:]

    # Apply ASSET modifications
    cpp_content = ensure_assets(cpp_content)

    # Apply transformations
    cpp_content = re.sub(r'setPose\(([-\d.]+),\s*([-\d.]+),\s*([-\d.]+)\)', 
                        mirror_setpose, cpp_content)
    
    # Handle swingToPoint separately
    cpp_content = re.sub(r'swingToPoint\(([-\d.]+),\s*([-\d.]+),\s*DriveSide::(RIGHT|LEFT)((?:,|,\s*{)[^)]*\))', 
                        mirror_swing_point, cpp_content)
    
    # Handle other Point functions
    cpp_content = re.sub(r'(moveTo|turnTo)Point\(([-\d.]+),\s*([-\d.]+)((?:,|,\s*{)[^)]*\))', 
                        mirror_point, cpp_content)
    
    cpp_content = re.sub(r'moveToPose\(([-\d.]+),\s*([-\d.]+),\s*([-\d.]+),\s*(\d+),\s*({[^}]*}),\s*(false|true)\)', 
                        mirror_pose, cpp_content)
    
    # Handle swingToHeading
    cpp_content = re.sub(r'swingToHeading\(([-\d.]+),\s*DriveSide::(RIGHT|LEFT)((?:,|,\s*{)[^)]*\))', 
                        lambda m: f'swingToHeading({mirror_angle(m.group(1))}, DriveSide::{"LEFT" if m.group(2)=="RIGHT" else "RIGHT"}{m.group(3)}', 
                        cpp_content)
    
    # Handle turnToHeading
    cpp_content = re.sub(r'turnToHeading\(([-\d.]+)((?:,|,\s*{)[^)]*\))', 
                        lambda m: f'turnToHeading({mirror_angle(m.group(1))}{m.group(2)}', 
                        cpp_content)

    # Update path in chassis.follow
    if 'blue' in input_file.lower():
        cpp_content = re.sub(r'chassis\.follow\(bl1_v2_txt,', 'chassis.follow(rr1_v2_txt,', cpp_content)
    else:
        cpp_content = re.sub(r'chassis\.follow\(rr1_v2_txt,', 'chassis.follow(bl1_v2_txt,', cpp_content)

    return cpp_content

def list_cpp_files(directory):
    cpp_files = []
    for file in os.listdir(directory):
        if file.endswith('.cpp') and ('blue' in file.lower() or 'red' in file.lower()):
            if not file.endswith('_temp.cpp'):  # Exclude temp files
                cpp_files.append(os.path.join(directory, file))
    return sorted(cpp_files)

def process_file(input_file):
    try:
        output_file = get_output_filename(input_file)
        
        with open(input_file, 'r') as f:
            content = f.read()
        
        mirrored_content = mirror_coordinates(content, input_file)
        
        with open(output_file, 'w') as f:
            f.write(mirrored_content)
            
        print(f"Successfully mirrored {os.path.basename(input_file)} to {os.path.basename(output_file)}")
        
    except FileNotFoundError:
        print(f"Error: Could not find input file {input_file}")
    except Exception as e:
        print(f"Error processing file: {str(e)}")
        raise

def main():
    if len(sys.argv) > 1:
        directory = sys.argv[1]
    else:
        directory = os.getcwd()
    
    cpp_files = list_cpp_files(directory)
    
    if not cpp_files:
        print("No suitable cpp files found in the directory.")
        return
    
    print("\nAvailable files:")
    for i, file in enumerate(cpp_files, 1):
        print(f"{i}. {os.path.basename(file)}")
    
    while True:
        try:
            selection = int(input("\nSelect a file to mirror (enter the number): "))
            if 1 <= selection <= len(cpp_files):
                break
            print("Invalid selection. Please try again.")
        except ValueError:
            print("Please enter a valid number.")
    
    selected_file = cpp_files[selection - 1]
    process_file(selected_file)

if __name__ == "__main__":
    main()