pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
                echo 'Building Unit Tests...'
		sh 'cmake .'
		sh 'make'
            }
        }
        stage('Running UTs') {
            steps {
                echo 'Running UTs'
                sh 'clang++ --version'
            }
        }
    }
}