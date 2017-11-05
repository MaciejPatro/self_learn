pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
                sh 'mkdir ../build'
                sh 'cd ../build'
                sh 'mkdir uts'
                sh 'cd uts'
		        sh 'cmake -D CMAKE_CXX_COMPILER=clang++ ../../../self_learn_repo'
		        sh 'make -j 4'
            }
        }
        stage('Running UTs') {
            steps {
                sh 'exercises/ut/exercisesTests -r junit > ut_results.xml'
            }
        }
        stage('Sanitizers') {
            steps {
                parallel(
                    Address: {
                        sh 'cmake -D CMAKE_CXX_COMPILER=clang++ -D asan=ON .'
                  	    sh 'make'
                        sh 'exercises/ut/exercisesTests'
                    },
                    Memory: {
                        sh 'cmake -D CMAKE_CXX_COMPILER=clang++ -D msan=ON .'
                  	    sh 'make'
                        sh 'exercises/ut/exercisesTests'
                    }
                )
		    }
        }
        stage('Build Product') {
            steps {
                sh 'cmake -D testing=OFF -D CMAKE_CXX_COMPILER=clang++ .'
                sh 'make -j 4'
            }
        }
    }
    post {
        always {
	    junit 'ut_results.xml'
	}
    }
}