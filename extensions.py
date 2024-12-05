def main():
    while True:
        parts = input("File name: ").lower().strip().rsplit(".", 1)
        if len(parts) == 2:
            check_extension(parts[1])
            break
        else:
            print("Invalid file name.Please enter again.")
            continue
    

    
def check_extension(extension):
    match extension:
        case 'gif':
            print("image/gif")
        case 'jpg':
            print("image/jpeg")
        case 'jpeg':
            print("image/jpeg")
        case 'png':
            print("image/png")
        case 'pdf':
            print("application/pdf")
        case 'txt':
            print("text/plain")
        case 'zip':
            print("application/zip")
        case _:
            print("application/octet-stream")
    

if __name__ == "__main__":
    main()