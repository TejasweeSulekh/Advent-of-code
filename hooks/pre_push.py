# This hook should update the readme before every push
import argparse
import os
import re
import subprocess
import math

def is_file_tracked(file_path):
    try:
        # Check if the file is tracked by Git
        subprocess.check_output(['git', 'ls-files', '--error-unmatch', file_path], stderr=subprocess.STDOUT)
        return True
    except subprocess.CalledProcessError:
        return False

def count_files(directory, valid_extensions):
    # Compile a regex pattern to match filenames
    file_pattern = re.compile(r'Part_([12])\.\w+')
    file_count = {'1': 0, '2': 0}

    # Walk through the directory recursively
    for root, _, filenames in os.walk(directory):
        for filename in filenames:
            # Look for a match with the pattern
            match = file_pattern.match(filename)
            if match:
                part = match.groups()
                file_path = os.path.join(root, filename)

                # Check if the file is tracked and has a valid extension 
                if is_file_tracked(file_path) and any(filename.lower().endswith(ext) for ext in valid_extensions):
                    file_count[part[0]] += 1

    return file_count

def calculate_progress(counts):
    # Sum up the total implementations found so far
    total_files = sum(counts.values())
    # Since the total number of problems to be done is 50 (each year) multiply by 2 to get percentage
    progress_percentage = total_files * 2
    return min(progress_percentage, 100)  # Cap the progress at 100%

def calculate_overall_progress(year_counts, total_years):
    expected_files = 25 * 2 * total_years * 2
    # expected_files = 25 *2
    actual_files = sum([data for data in year_counts.values()])
    overall_progress_percentage = min(math.floor((actual_files / expected_files) * 100), 100)
    return overall_progress_percentage

def count_files_in_years(root_directory, valid_extensions, dry_run=False):
    # Complile a regex pattern to match year file name
    year_pattern = re.compile(r'^AOC\d{4}$') # Here '^' and '\d{num}' represent the starting of the string, digits (num is the number of digits)
                                             # While '$' represent the ending of the string
    year_progress = {}

    for subdir in os.listdir(root_directory):
        # Assume that the file containing the year-wise folders is one step away
        year_path = os.path.join(root_directory, subdir)

        # checks if the path is a directory and then checks if it also matches the pattern
        if os.path.isdir(year_path) and year_pattern.match(subdir):
            # Get the total questions done in that year
            counts = count_files(year_path, valid_extensions)
            # Calculate that year's progress
            progress = calculate_progress(counts)
            # Append that to the dict
            year_progress[subdir[3:]] = progress
        
            if dry_run:
                # print(f"Year: {subdir}, Progress: {year_progress[subdir]}")
                print(f"Year {subdir}: Part 1 - {counts['1']}, Part 2 - {counts['2']}, Progress - {progress}%")

    return year_progress

def update_readme_with_progress(readme_path, year_progress, overall_progress):
    with open(readme_path, 'r') as file:
        readme_content = file.read()
    # Compile a regex to look for the progress bar pattern
    overall_pattern = re.compile(r'!\[Progress Bar to show how much progress has been made\]\(https://progress-bar.xyz/\d+/\?title=Progress\)')
    overall_content = f"![Progress Bar to show how much progress has been made](https://progress-bar.xyz/{overall_progress}/?title=Progress)"
    readme_content = overall_pattern.sub(overall_content, readme_content)

    # Goes over all the years found in the direc with the progress percentage
    for year, progress in year_progress.items():
        # Compiles the pattern for year-wise
        year_pattern = re.compile(fr'!\[Progress Bar to show how much progress has been made in the {year} problems\]\(https://progress-bar.xyz/\d+/\?title={year}\)')
        # The substitute
        year_content = f"![Progress Bar to show how much progress has been made in the {year} problems](https://progress-bar.xyz/{progress}/?title={year})"
        # Update in the file
        readme_content = year_pattern.sub(year_content, readme_content)

    with open(readme_path, 'w') as file:
        # Write the updated content to the file
        print(readme_content)
        file.write(readme_content)

def commit_readme_changes(commit_message, readme_path):
    # Commits the readme file (Supposed to be run after updating the readme)
    os.system(f"git add {readme_path}")
    os.system(f"git commit -m \"{commit_message}\"")

def run_clang_format(directory, file_extensions, years, dry_run=False):
    formatted_files = []
    
    # Constructing list of directories to look at
    target_directories = [f"AOC{year}/Day{day}" for year in years for day in range(1,26)]
    
    # Recursive walk looking for the target direcories
    for root, _, filenames in os.walk(directory):
        # When in the target folder
        if root.endswith(tuple(target_directories)):
            # Go over all the files
            for filename in filenames:
                # Looks for the valid extension for clang formatting
                if filename.endswith(tuple(file_extensions)):
                    # Creates the whole path
                    file_path = os.path.join(root, filename)
                    # Check if the file is tracked
                    if is_file_tracked(file_path):
                        if not dry_run:
                            os.system(f"clang-format --style=file -i {file_path}")
                        formatted_files.append(file_path)

    return formatted_files

def commit_formatted_files(formatted_files, commit_message, dry_run=False):
    if formatted_files and not dry_run:
        # Prepares the files for git commit
        formatted_files_str = ' '.join(formatted_files)
        os.system(f"git add {formatted_files_str}")
        os.system(f"git commit -m \"{commit_message}\"")

def main():
    parser = argparse.ArgumentParser(description='Script for updating progress and formatting code.')
    parser.add_argument('--dry_run', '-d', action='store_true', help='Run in dry-run mode (no actual changes will be made)')
    args = parser.parse_args()
    drier = True
    # root_directory = "./"
    root_directory = "."
    # The extensions that will be considered for the counting
    valid_extensions = ['.cpp', '.java', '.py', '.rs']

    # year_progress = count_files_in_years(root_directory, valid_extensions, dry_run=args.dry_run)
    year_progress = count_files_in_years(root_directory, valid_extensions, drier)
    # Total years which are being done
    total_years = len(year_progress)

    years = ['2022', '2023', '2024']
    # formatted_files = run_clang_format(root_directory, ['.cpp', '.hpp'], target_directories, dry_run=args.dry_run)
    formatted_files = run_clang_format(root_directory, ['.cpp', '.hpp'], years, drier)
    
    # commit_formatted_files(formatted_files, r"Formatted the files using \`clang-format\`.", dry_run=args.dry_run)
    commit_formatted_files(formatted_files, r"Formatted the files using \`clang-format\`.", drier)
    

    overall_progress = calculate_overall_progress(year_progress, total_years)
    
    # dummyAddress = "/home/tejaswee/VScode/cpp/files/Advent-of-code/"
    
    readme_path = "./README.md"
    update_readme_with_progress(readme_path, year_progress, overall_progress)
    commit_message = "Updated README to reflect current progress using pre-push git hook."
    commit_readme_changes(commit_message, readme_path)

if __name__ == "__main__":
    main()